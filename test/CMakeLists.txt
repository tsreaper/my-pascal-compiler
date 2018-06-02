include_directories(.)

add_custom_target(
        mpc-test
        DEPENDS mpc-test-normal mpc-test-example mpc-test-error
)

add_custom_target(
        mpc-test-normal bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ok.sh ${CMAKE_BINARY_DIR}/src/mpc normal
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)

add_custom_target(
        mpc-test-example bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ok.sh ${CMAKE_BINARY_DIR}/src/mpc example
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)

add_custom_target(
        mpc-test-error bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ce.sh ${CMAKE_BINARY_DIR}/src/mpc error
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)
