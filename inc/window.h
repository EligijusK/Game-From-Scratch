//
// Created by Eligijus Kiudys on 2021-06-30.
//

#ifndef GAME_FROM_SCRACH_WINDOW_H
#define GAME_FROM_SCRACH_WINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include "GLFW/glfw3.h"

class Window
{
private:
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    int width;
    int height;
    GLFWwindow* window;

public:
    Window(int width, int height);
    void destroy_window();
    void clear_viewport();
    void swap_buffer();
    bool run();
};

#endif //GAME_FROM_SCRACH_WINDOW_H
