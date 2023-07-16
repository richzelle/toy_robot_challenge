set(BINARY ${CMAKE_PROJECT_NAME})

include_directories(../include)

file(GLOB SOURCES *.cpp)
set(SOURCES ${SOURCES})

add_executable(toy_robot ${SOURCES})

add_library(toy_robot_lib STATIC ${SOURCES})

target_link_libraries(toy_robot PUBLIC ${CONAN_LIBS})