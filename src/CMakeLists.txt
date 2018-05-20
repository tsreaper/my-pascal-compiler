include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

aux_source_directory(ast AST_SOURCE)
aux_source_directory(ast/const AST_SOURCE)
aux_source_directory(ast/id AST_SOURCE)
aux_source_directory(ast/label AST_SOURCE)
aux_source_directory(ast/program AST_SOURCE)
aux_source_directory(ast/type AST_SOURCE)

aux_source_directory(env ENV_SOURCE)
aux_source_directory(env/id ENV_SOURCE)
aux_source_directory(env/label ENV_SOURCE)
aux_source_directory(env/type ENV_SOURCE)
aux_source_directory(env/value ENV_SOURCE)

add_custom_command(
        OUTPUT pascal.l.cpp
        COMMAND echo ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND pwd
        COMMAND flex -o pascal.l.cpp ${CMAKE_CURRENT_LIST_DIR}/flex/pascal.l
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/flex/pascal.l pascal.y.hpp
)
add_custom_command(
        OUTPUT pascal.y.cpp pascal.y.hpp
        COMMAND echo ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND pwd
        COMMAND bison -d -o pascal.y.cpp ${CMAKE_CURRENT_LIST_DIR}/bison/pascal.y
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bison/pascal.y
)

add_executable(
        my_pascal
        main.cpp ${AST_SOURCE} ${ENV_SOURCE}
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.l.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.cpp ${CMAKE_CURRENT_BINARY_DIR}/pascal.y.hpp
)