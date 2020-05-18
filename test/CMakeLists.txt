include_directories(.)

add_custom_target(
        mpc-test
        DEPENDS mpc-test-normal mpc-test-example mpc-test-validation
)

add_custom_target(
        mpc-test-normal bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ok.sh ${PROJECT_BINARY_DIR}/src/mpc normal
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)

add_custom_target(
        mpc-test-example bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ok.sh ${PROJECT_BINARY_DIR}/src/mpc example
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)

add_custom_target(
        mpc-test-validation bash ${CMAKE_CURRENT_SOURCE_DIR}/test_ce.sh ${PROJECT_BINARY_DIR}/src/mpc validation
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mpc
)
