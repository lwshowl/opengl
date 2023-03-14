#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "shader.h"
#include "mesh.h"

class model
{
public:
    std::vector<mesh> meshes;

    model()
    {
    }

    virtual void init()
    {
    }

    void render(Shader shader)
    {
        for (auto mesh : meshes)
        {
            mesh.render(shader);
        }
    }

    void cleanup()
    {
        for (auto mesh : meshes)
        {
            mesh.cleanup();
        }
    }
};