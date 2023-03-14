#pragma once

#include "camera.h"
#include "mouse.h"
#include <iostream>

static uint32_t window_width = 2000;
static uint32_t window_height = 1100;
static Camera camera({0.0f, 0.0f, 3.0f});

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

GLFWwindow *initWindow(unsigned int width,unsigned int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "opengl", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialze GLAD" << std::endl;
        return 0;
    }

    return window;
}

static void processingInput(GLFWwindow *window, double dt)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.setPos(FORWARD, dt);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.setPos(BACKWARD, dt);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.setPos(LEFT, dt);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.setPos(RIGHT, dt);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.setPos(UP, dt);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        camera.setPos(DOWN, dt);
    }

    double dx = Mouse::getDX() * 0.3, dy = Mouse::getDY() * 0.3;
    double scrollDy = Mouse::getScrollDY();

    if (dx != 0 || dy != 0)
    {
        camera.setYawPitch(dx, dy);
    }

    if (scrollDy != 0)
    {
        camera.setZoom(scrollDy);
    }
}
