#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mouse.h"

class viewport
{

private:
    GLFWwindow *window;

public:
    unsigned int width;
    unsigned int height;
    
    viewport(GLFWwindow *window,unsigned int width ,unsigned int height)
    {
        this->window = window;
        this->width = width;
        this->height = height;
        glViewport(0, 0, width, height);

        glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
        glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
        glfwSetScrollCallback(window, Mouse::mouseWheelCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void init()
    {
    }

    bool shouldClose()
    {
    }

    void setShouldClose(bool close);
};