#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class texture
{
public:
    static int glob_id;
    std::string path;
    int width;
    int height;
    int channels;
    std::string name;
    unsigned int id;

    texture()
    {
    }
    texture(std::string path, std::string name, bool defaultParams = true);
    void generate();
    void setFilters(GLenum all);
    void setFilters(GLenum mag, GLenum min);
    void bind();
    void setWrap(GLenum all);
    void setWrap(GLenum s, GLenum t);
    void activate();
    void load(bool flip = true);
};
