//
// Created by Eligijus Kiudys on 2021-07-01.
//

#ifndef GAME_FROM_SCRACH_TEXTURE_H
#define GAME_FROM_SCRACH_TEXTURE_H

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <string>

class Texture {
public:
    Texture(const std::string &fileName);

    void bind(unsigned int index);

    virtual ~Texture();

private:
    Texture(const Texture &other);
    void operator = (const Texture &other);
    GLuint m_texture;
};


#endif //GAME_FROM_SCRACH_TEXTURE_H
