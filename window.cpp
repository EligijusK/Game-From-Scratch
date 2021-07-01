#include "include/GLFW/glfw3.h"
#include "inc/window.h"
#define GLFW_INCLUDE_NONE

//
// Created by Eligijus Kiudys on 2021-06-30.
//

void Window::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window(int height, int width)
{
    this->height = height;
    this->width = width;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(height, width, "Simple example", NULL, NULL); // 640 480
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);

    //gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

}



bool Window::run()
{
    return !glfwWindowShouldClose(window);
}

void Window::destroy_window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::clear_viewport()
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap_buffer()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
