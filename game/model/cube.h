#pragma once

#include "model.h"
#include "shapes.h"
#include "texture.h"

class cube : public model
{
public:
    glm::vec3 pos;
    glm::vec3 size;
    texture tex;

    cube(glm::vec3 pos, glm::vec3 size, texture texture)
    {
        this->pos = pos;
        this->size = size;
        this->tex = texture;
        init();
    }

    void init() override
    {
        int noVerticies = 36;
        // vertex array

        std::vector<unsigned int> indicies(noVerticies);
        for (int i = 0; i < noVerticies; i++)
            indicies[i] = i;

        auto vec_vertcies = vertex::genList(cube_vertices, noVerticies);
        // texture t("assets/texture/door.png", "texture1");

        meshes.emplace_back(mesh(vec_vertcies, indicies, {tex}));
    }

    void render(Shader shader)
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5));
        model = glm::scale(model, size);
        model = glm::translate(model, pos);
        shader.uniformMat4("model", model);

        model::render(shader);
    }
};