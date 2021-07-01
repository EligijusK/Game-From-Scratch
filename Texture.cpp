//
// Created by Eligijus Kiudys on 2021-07-01.
//
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "inc/Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string &fileName)
{
    int width, height, numComponent;

    stbi_uc *imageData = stbi_load(fileName.c_str(), &width, &height, &numComponent, 4);

    if(imageData == NULL)
        std::cout << "Failed to load image";

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);


    stbi_image_free(imageData);
}

Texture::~Texture()
{
    glDeleteTextures(4, &m_texture);
}

void Texture::bind(unsigned int index)
{
    assert(index >= 0 && index <= 32);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
