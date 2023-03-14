#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>

class Shader
{
private:
    std::string vertexShader;
    std::string fragmentShader;
    GLuint programID;

    std::string loadShader(std::string path)
    {
        std::ifstream file;
        std::stringstream ss;

        file.open(path);
        if (file.is_open() == false)
        {
            std::cout << "could not open " + path + "\n";
            file.close();
            return std::string();
        }
        ss << file.rdbuf();
        file.close();
        return ss.str();
    }

public:
    Shader(std::string vertex_path, std::string frag_path)
    {
        vertexShader = loadShader(vertex_path);
        fragmentShader = loadShader(frag_path);
    }

    GLuint getProgramID()
    {
        return programID;
    }

    void uniformMat4(std::string name, glm::mat4 mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.data()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void uniformInt(std::string name, int value)
    {
        glUniform1i(glGetUniformLocation(programID, name.data()), value);
    }

    void activate()
    {
        glUseProgram(programID);
    }

    void compile()
    {
        unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *shaderCode = vertexShader.data();
        glShaderSource(vertexID, 1, &shaderCode, NULL);
        glCompileShader(vertexID);
        static char buffer[256];
        int success;
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexID, 256, NULL, buffer);
            std::cout << "error compile vertex shader :\n"
                      << buffer << "\n";
        }

        shaderCode = fragmentShader.data();
        glShaderSource(fragmentID, 1, &shaderCode, NULL);
        glCompileShader(fragmentID);
        glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentID, 256, NULL, buffer);
            std::cout << "error compile fragment shader :\n"
                      << buffer << "\n";
        }

        programID = glCreateProgram();
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);
        glLinkProgram(programID);

        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(programID, 256, NULL, buffer);
            std::cout << "error linking program :\n"
                      << buffer << "\n";
        }

        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
    }
};
