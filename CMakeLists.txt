cmake_minimum_required(VERSION 3.14)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 11)

##############################################################
# Project folder structure
##############################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PROJECT_SOURCE_DIR src)
set(EXTERNAL_LIBRARIES ext)

##############################################################
# Build ext
##############################################################
add_subdirectory("${EXTERNAL_LIBRARIES}/glfw")
add_subdirectory("${EXTERNAL_LIBRARIES}/glad")

##############################################################
# Includes
##############################################################
include_directories("${EXTERNAL_LIBRARIES}/glfw/include")
include_directories("${EXTERNAL_LIBRARIES}/glad/include")
include_directories("${EXTERNAL_LIBRARIES}/sb7/include")

##############################################################
# Shaders
##############################################################
add_library(ShaderCompilation ${PROJECT_SOURCE_DIR}/ShaderCompiler/ShaderCompiler.cpp)
target_include_directories(ShaderCompilation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

##############################################################
# Build
##############################################################
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} ShaderCompilation ${SHADERCOMPILATION_LIBRARIES})

##############################################################
# 'Link' Shaders
##############################################################
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/src/Shaders
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
)
