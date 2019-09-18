#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include <glad/glad.h>

#include "ShaderCompiler.hpp"


#define GLSL_VERSION_410 "#version 410 core\n"
#define GLSL_VERSION_450 "#version 450 core\n"


std::string ReadShaderFile(const char* file_path) {
    std::string file_string;
    std::ifstream stream(file_path, std::ios::in);


#if __APPLE__
    file_string += GLSL_VERSION_410;
#else
    file_string += GLSL_VERSION_450;
#endif

    if(stream.is_open()){
        std::string line;
        while(getline(stream, line)){
            file_string += "\n" + line;
        }
        stream.close();
    } else {
        std::cout << "Cannot open '" << file_path << "'" << std::endl;
        exit(-1);
    }
    return file_string;
}

GLuint CompileShader(const char* code, GLenum type) {
    GLuint shaderId   = glCreateShader(type);

    GLint result = 0;
    int infoLogLength = 512;
    std::array<char, 512> infoLog = {};

    // Compile Vertex Shader
    glShaderSource(shaderId, 1, &code , nullptr);
    glCompileShader(shaderId);

    // Check Vertex Shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog.data() << std::endl;
        exit(-1);
    }

    return shaderId;
}

GLuint CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
    GLuint programID = glCreateProgram();
    GLint result = 0;
    int infoLogLength = 512;
    std::array<char, 512> infoLog = {};

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(!result){
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, infoLog.data());
        std::cout << "ERROR::PROGRAM::LINKING_FAILED: " << infoLog.data() << std::endl;
        exit(-1);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    std::cout << "Creating Shader Program with [" << vertex_file_path << "] and [" << fragment_file_path << "]." << std::endl;

    // Read shaders from file path
    std::string vertexShaderCode = ReadShaderFile(vertex_file_path);
    std::string fragmentShaderCode = ReadShaderFile(fragment_file_path);

    // Compile shaders and create program
    GLuint vertexShaderID   = CompileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShaderID = CompileShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
    GLuint programID = CreateProgram(vertexShaderID, fragmentShaderID);

    return programID;
}
