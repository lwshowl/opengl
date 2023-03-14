#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"
#include "texture.h"

typedef struct vertex vertex;
struct vertex
{
    glm::vec3 pos;
    glm::vec2 texCoord;
    static inline std::vector<vertex> genList(float *verticies, int num)
    {
        std::vector<vertex> ret(num);
        int stride = sizeof(vertex) / sizeof(float);

        for (int i = 0; i < num; i++)
        {
            ret[i].pos = glm::vec3{verticies[i * stride + 0],
                                   verticies[i * stride + 1],
                                   verticies[i * stride + 2]};

            ret[i].texCoord = glm::vec2{verticies[i * stride + 3],
                                        verticies[i * stride + 4]};
        }

        return ret;
    }
};

class mesh
{
public:
    std::vector<vertex> verticies;
    std::vector<unsigned int> indicies;
    std::vector<texture> textures;
    unsigned int VAO, VBO, EBO;

    mesh()
    {
    }

    mesh(const std::vector<vertex> &verticies,
         const std::vector<unsigned int> &indicies,
         const std::vector<texture> &textures)
    {
        this->verticies = verticies;
        this->indicies = indicies;
        this->textures = textures;
        setup();
    }

    void setup()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(vertex), verticies.data(), GL_STATIC_DRAW);

        // bind EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);

        // set attribute array
        // verticies
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, pos));
        glEnableVertexAttribArray(0);
        // texture verticies
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, texCoord));
        glEnableVertexAttribArray(1);
    }

    void render(Shader shader)
    {
        for (auto texture : textures)
        {
            shader.uniformInt(texture.name, texture.id);
            texture.activate();
            texture.bind();
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(0);
    }

    void cleanup()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};