include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

aux_source_directory(ast AST_SOURCE)
aux_source_directory(ast/func AST_SOURCE)
aux_source_directory(ast/id AST_SOURCE)
aux_source_directory(ast/label AST_SOURCE)
aux_source_directory(ast/program AST_SOURCE)
aux_source_directory(ast/type AST_SOURCE)
aux_source_directory(ast/value AST_SOURCE)

aux_source_directory(sem SEM_SOURCE)
aux_source_directory(sem/exception SEM_SOURCE)
aux_source_directory(sem/func SEM_SOURCE)
aux_source_directory(sem/id SEM_SOURCE)
aux_source_directory(sem/label SEM_SOURCE)
aux_source_directory(sem/type SEM_SOURCE)
aux_source_directory(sem/value SEM_SOURCE)

file(
        GLOB BISON_SOURCE
        bison/*.y
        bison/func/*.y
        bison/id/*.y
        bison/label/*.y
        bison/program/*.y
        bison/type/*.y
        bison/value/*.y
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

add_executable(
        my_pascal
        main.cpp ${AST_SOURCE} ${SEM_SOURCE}
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.l.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.cpp ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.hpp
)