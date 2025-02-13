#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 2

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

GLFWwindow *TestSetup(const int initWindowWidth, const int initWindowHeight, void(*windowHintFunction)())
{
    if(glfwInit() == GLFW_FALSE)
    {
        std::fputs("GLFW initialization failed!\n", stderr);
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(windowHintFunction)
        windowHintFunction();
    GLFWwindow *window = glfwCreateWindow(initWindowWidth, initWindowHeight, "general test", nullptr, nullptr);
    if(!window)
    {
        const char *error;
        glfwGetError(&error);
        std::fprintf(stderr, "Failed to create glfw window: %s\n", error);
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if(const GLenum err = glewInit() != GLEW_OK)
    {
        std::fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return nullptr;
    }

    return window;
}