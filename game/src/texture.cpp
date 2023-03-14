#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int texture::glob_id = 0;

texture::texture(std::string path, std::string name, bool defaultParams)
{
    this->path = path;
    this->name = name;
    id = glob_id++;
    generate();
    load();
    if (defaultParams)
    {
        setFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
        setWrap(GL_REPEAT);
    }
}

void texture::generate()
{
    glGenTextures(1, &id);
}

void texture::setFilters(GLenum all)
{
    setFilters(all, all);
}
void texture::setFilters(GLenum mag, GLenum min)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void texture::setWrap(GLenum all)
{
    setWrap(all, all);
}

void texture::setWrap(GLenum s, GLenum t)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void texture::activate()
{
    glActiveTexture(GL_TEXTURE0 + id);
}

void texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void texture::load(bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(path.data(), &width, &height, &channels, 0);
    GLenum colorMode = GL_RGB;

    switch (channels)
    {
    case 1:
        colorMode = GL_RED;
        break;
    case 4:
        colorMode = GL_RGBA;
        break;
    }

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "failed to load texture\n";
    }

    stbi_image_free(data);
}