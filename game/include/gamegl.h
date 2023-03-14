#pragma once

#include "camera.h"
#include "mouse.h"

static uint32_t window_width = 2000;
static uint32_t window_height = 1100;
static Camera camera({0.0f, 0.0f, 3.0f});

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
