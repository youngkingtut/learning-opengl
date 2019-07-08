#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include <glad/glad.h>

#include "ShaderCompiler.hpp"


GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path){
    // Create the shaders
    GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
    if(vertexShaderStream.is_open()){
        std::string line;
        while(getline(vertexShaderStream, line)){
            vertexShaderCode += "\n" + line;
        }
        vertexShaderStream.close();
    } else {
        std::cout
                << "Impossible to open '"
                << vertex_file_path
                << "' Are you in the right directory?";
        exit(-1);
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if(fragmentShaderStream.is_open()){
        std::string line;
        while(getline(fragmentShaderStream, line)){
            fragmentShaderCode += "\n" + line;
        }
        fragmentShaderStream.close();
    } else {
        std::cout
                << "Impossible to open '"
                << fragment_file_path
                << "' Are you sure you're in the right directory?";
        exit(-1);
    }

    GLint result = 0;
    int infoLogLength = 512;
    char infoLog[infoLogLength];


    // Compile Vertex Shader
    std::cout << "Compiling shader: '" << vertex_file_path << "'";
    char const* VertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(vertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED:" << infoLog;
        exit(-1);
    }

    // Compile Fragment Shader
    std::cout << "Compiling shader: '" << fragment_file_path << "'";
    char const * FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(fragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    // TODO: Compromising solution until Tristan can get down and figure out why his
    // systems return 1 to the infoLogLength (log has no info)
    if(infoLogLength > 1){
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
        std::cout << &fragmentShaderErrorMessage[0];
        exit(-1);
    }

    // Link the program
    std::cout << "Linking program";
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    // TODO: Compromising solution until Tristan can get down and figure out why his
    // systems return 1 to the infoLogLength (log has no info)
    if(infoLogLength > 1){
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, &programErrorMessage[0]);
        std::cout << &programErrorMessage[0];
        exit(-1);
    }


    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}
