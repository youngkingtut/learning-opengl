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
add_definitions(-DGLFW_INCLUDE_NONE)

##############################################################
# Includes
##############################################################
include_directories("${EXTERNAL_LIBRARIES}/glfw/include")
include_directories("${EXTERNAL_LIBRARIES}/glad/include")
include_directories("${EXTERNAL_LIBRARIES}/sb7/include")

##############################################################
# Build
##############################################################
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/Interface/Window.cpp
        src/Interface/Window.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Game/World.cpp
        src/Game/World.h
        src/Game/Objects/Player.cpp
        src/Game/Objects/Player.h
        src/Utils/Constants.h
        src/Interface/ControlState.cpp
        src/Interface/ControlState.h
        src/ShaderCompiler/ShaderCompiler.cpp
        src/ShaderCompiler/ShaderCompiler.hpp
        src/Game/Objects/WorldObject.cpp
        src/Game/Objects/WorldObject.h
        src/Game/Objects/Bullet.cpp
        src/Game/Objects/Bullet.h src/Game/WorldState.h)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad)

##############################################################
# 'Link' Shaders
##############################################################
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/src/Shaders
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders
)
