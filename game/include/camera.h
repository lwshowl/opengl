#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraDirection
{
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
private:
    glm::vec3 pos;
    glm::vec3 lok_dir;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 front;

    glm::vec3 world_up;

public:
    double pitch;
    double yaw;
    double speed;
    double sensitivity;
    double zoom;

    Camera(glm::vec3 position)
    {
        pos = position;
        world_up = {0.0f, 1.0f, 0.0f};
        yaw = -90.0f;
        pitch = 0;
        speed = 2.5f;
        zoom = 45.0f;
        front = {0.0f, 0.0f, -1.0f};
        updateInternal();
    }
    void update();

    void setYawPitch(double dx, double dy)
    {
        yaw += dx;
        pitch += dy;

        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        else if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
        updateInternal();
    }

    void setPos(CameraDirection dir, double dt)
    {
        float velocity = (float)(dt * speed);
        switch (dir)
        {
        case FORWARD:
            pos += front * velocity;
            break;
        case BACKWARD:
            pos -= front * velocity;
            break;
        case RIGHT:
            pos += right * velocity;
            break;
        case LEFT:
            pos -= right * velocity;
            break;
        case UP:
            pos += up * velocity;
            break;
        case DOWN:
            pos -= up * velocity;
            break;
        }

        updateInternal();
    }

    void setZoom(double dy)
    {
        if (zoom > 1.0f && zoom <= 45.0f)
        {
            zoom -= dy;
        }
        else if (zoom < 1.0f)
        {
            zoom = 1.0f;
        }
        else
        {
            zoom = 45.0f;
        }
    }

    glm::mat4 view()
    {
        return glm::lookAt(pos, pos + front, up);
    }

    void updateInternal()
    {
        glm::vec3 dir;
        dir.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
        dir.y = (float)(sin(glm::radians(pitch)));
        dir.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        front = glm::normalize(dir);

        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));
    }

    double getZoom()
    {
        return zoom;
    }
};
