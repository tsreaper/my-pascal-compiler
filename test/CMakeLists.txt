include_directories(.)

add_custom_target(
        mpc_test bash ${CMAKE_CURRENT_SOURCE_DIR}/test.sh ${CMAKE_BINARY_DIR}/src/mpc
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)
