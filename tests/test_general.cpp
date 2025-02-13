#include <cstdio>
#include "test_setup.hpp"
int main()
{
    GLFWwindow *window = TestSetup(1200, 675, nullptr);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    return 0;
}