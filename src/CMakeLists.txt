include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

aux_source_directory(ast AST_SOURCE)
aux_source_directory(ast/exp AST_SOURCE)
aux_source_directory(ast/exp/arith AST_SOURCE)
aux_source_directory(ast/exp/array AST_SOURCE)
aux_source_directory(ast/exp/cmp AST_SOURCE)
aux_source_directory(ast/exp/logic AST_SOURCE)
aux_source_directory(ast/exp/ptr AST_SOURCE)
aux_source_directory(ast/exp/record AST_SOURCE)
aux_source_directory(ast/func AST_SOURCE)
aux_source_directory(ast/label AST_SOURCE)
aux_source_directory(ast/id AST_SOURCE)
aux_source_directory(ast/program AST_SOURCE)
aux_source_directory(ast/stmt AST_SOURCE)
aux_source_directory(ast/stmt/cond AST_SOURCE)
aux_source_directory(ast/stmt/loop AST_SOURCE)
aux_source_directory(ast/type AST_SOURCE)
aux_source_directory(ast/type/builtin AST_SOURCE)
aux_source_directory(ast/val AST_SOURCE)
aux_source_directory(ast/val/literal AST_SOURCE)

aux_source_directory(sem SEM_SOURCE)
aux_source_directory(sem/exception SEM_SOURCE)
aux_source_directory(sem/exp SEM_SOURCE)
aux_source_directory(sem/func SEM_SOURCE)
aux_source_directory(sem/func/sys SEM_SOURCE)
aux_source_directory(sem/label SEM_SOURCE)
aux_source_directory(sem/id SEM_SOURCE)
aux_source_directory(sem/stmt SEM_SOURCE)
aux_source_directory(sem/type SEM_SOURCE)
aux_source_directory(sem/val SEM_SOURCE)

aux_source_directory(gen GEN_SOURCE)
aux_source_directory(gen/exp GEN_SOURCE)
aux_source_directory(gen/func GEN_SOURCE)
aux_source_directory(gen/func/sys GEN_SOURCE)
aux_source_directory(gen/label GEN_SOURCE)
aux_source_directory(gen/id GEN_SOURCE)
aux_source_directory(gen/program GEN_SOURCE)
aux_source_directory(gen/stmt GEN_SOURCE)
aux_source_directory(gen/type GEN_SOURCE)
aux_source_directory(gen/val GEN_SOURCE)

aux_source_directory(make MAKE_SOURCE)

file(
        GLOB BISON_SOURCE
        bison/*.y
        bison/exp/*.y
        bison/func/*.y
        bison/func/sys/*.y
        bison/id/*.y
        bison/label/*.y
        bison/program/*.y
        bison/stmt/*.y
        bison/type/*.y
        bison/val/*.y
)
list(REMOVE_ITEM BISON_SOURCE ${CMAKE_CURRENT_LIST_DIR}/bison/head.y)

add_custom_command(
        OUTPUT pascal.l.cpp
        COMMAND flex -o pascal.l.cpp ${CMAKE_CURRENT_LIST_DIR}/flex/pascal.l
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/flex/pascal.l pascal.y.hpp
)
add_custom_command(
        OUTPUT pascal.y.cpp pascal.y.hpp
        COMMAND bison -d -o pascal.y.cpp pascal.build.y
        DEPENDS pascal.build.y
)
add_custom_command(
        OUTPUT pascal.build.y
        COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/bison/build.sh pascal.build.y ${CMAKE_CURRENT_LIST_DIR}/bison/head.y ${BISON_SOURCE}
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bison/head.y ${BISON_SOURCE} ${CMAKE_CURRENT_LIST_DIR}/bison/build.sh
)

if(APPLE)
llvm_map_components_to_libnames(LLVM_LINK_LIBRARIES core)
ELSE()
execute_process(COMMAND llvm-config --libs OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)
ENDIF()

add_executable(
        mpc
        main.cpp ${AST_SOURCE} ${SEM_SOURCE} ${GEN_SOURCE} ${MAKE_SOURCE}
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.l.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.cpp ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.hpp
)

set_target_properties(mpc PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
