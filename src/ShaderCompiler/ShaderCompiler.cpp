#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include <glad/glad.h>

#include "ShaderCompiler.hpp"

std::string ReadShaderFile(const char* file_path) {
    std::cout << "Reading: " << file_path << std::endl;

    std::string file_string;
    std::ifstream stream(file_path, std::ios::in);
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
    std::cout << "Compiling shader: " << type << std::endl;

    GLuint shaderId   = glCreateShader(type);

    GLint result = 0;
    int infoLogLength = 512;
    char infoLog[infoLogLength];

    // Compile Vertex Shader
    glShaderSource(shaderId, 1, &code , nullptr);
    glCompileShader(shaderId);

    // Check Vertex Shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog;
        exit(-1);
    }

    return shaderId;
}


GLuint CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
    std::cout << "Creating Program" << std::endl;

    GLuint programID = glCreateProgram();
    GLint result = 0;
    int infoLogLength = 512;
    char infoLog[infoLogLength];

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(!result){
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED: " << infoLog;
        exit(-1);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    // Read shaders from file path
    std::string vertexShaderCode = ReadShaderFile(vertex_file_path);
    std::string fragmentShaderCode = ReadShaderFile(fragment_file_path);

    // Compile shaders and create program
    GLuint vertexShaderID   = CompileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShaderID = CompileShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
    GLuint programID = CreateProgram(vertexShaderID, fragmentShaderID);

    return programID;
}
