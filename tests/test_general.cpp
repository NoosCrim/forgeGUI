#include <cstdio>
#include "test_setup.hpp"
#include <baseGUIquad.hpp>
int main()
{
    GLFWwindow *window = testSetup(1200, 675, nullptr);
    forgeGUI::BaseQuad testBaseQuad1({100,100}, {0,0}, {1.f,0.f,0.f,1.f});
    forgeGUI::BaseQuad testBaseQuad2({100,100}, {100,0}, {0.f,1.f,0.f,1.f});
    forgeGUI::BaseQuad testBaseQuad3({100,100}, {200,0}, {0.f,0.f,1.f,1.f});
    glfwSwapInterval(1);
    glViewport(0, 0, 1200, 675);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1,0,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        forgeGUI::BaseQuad::DrawAll({1200, 675});
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}