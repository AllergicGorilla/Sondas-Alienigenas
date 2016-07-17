cmake_minimum_required(VERSION 2.8)
project(GLFWTest)
aux_source_directory("src" SOURCES)
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)


find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

SET(GCC_COVERAGE_LINK_FLAGS "-lGL -ldl")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#Copies the shaders dir to where the project is being built
file(COPY "shaders" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
