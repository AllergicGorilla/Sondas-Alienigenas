cmake_minimum_required(VERSION 2.8)
project(GLFWTest)
aux_source_directory("src" SOURCES)
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)


SET(GCC_COVERAGE_LINK_FLAGS "-lGL -ldl")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Copy shaders directory to build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
									 ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
# Copy images directory to build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
									 ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:${PROJECT_NAME}>/images)
