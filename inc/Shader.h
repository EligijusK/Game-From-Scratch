//
// Created by Eligijus Kiudys on 2021-06-30.
//

#ifndef GAME_FROM_SCRACH_SHADER_H
#define GAME_FROM_SCRACH_SHADER_H


#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#else
    #include <GL/glew.h>
#endif
//#include <GL/.h> // include glad to get all the required OpenGL headers
#include "camera.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
private:
    static unsigned int program;
public:
// the program ID
    // constructor reads and builds the shader
    Shader(std::string vertexPath, std::string fragmentPath);

    static GLuint get_shader_index(char *name)
    {
        return glGetAttribLocation(Shader::program, name);
    }

    // use/activate the shader
    void use();

    void update(Camera camera);
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVector3(const std::string &name, float value[]) const;

    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif