set(BINARY ${CMAKE_PROJECT_NAME}_tests)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

include_directories(../include ${GTEST_INCLUDE_DIRS})

add_executable(${BINARY} ${TEST_SOURCES})
target_link_libraries(${BINARY} PUBLIC toy_robot_lib gtest pthread)