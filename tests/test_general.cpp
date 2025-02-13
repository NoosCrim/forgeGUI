#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
int main()
{
    int initWindowWidth = 1200, initWindowHeight = 675;
    if(glfwInit() == GLFW_FALSE)
    {
        std::fputs("GLFW initialization failed!\n", stderr);
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(initWindowWidth, initWindowHeight, "general test", nullptr, nullptr);
    if(!window)
    {
        const char *error;
        glfwGetError(&error);
        std::fprintf(stderr, "Failed to create glfw window: %s\n", error);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(const GLenum err = glewInit() != GLEW_OK)
    {
        std::fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    return 0;
}