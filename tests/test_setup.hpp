#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 3

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
static void glfw_error_callback(int error, const char* description)
{
	std::fprintf(stderr, "GLFW error %d: %s\n", error, description);
}
static void GLAPIENTRY gl_error_callback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
{
    (void)source;
    (void)id;
    (void)length;
    (void)userParam;

	if(type == GL_DEBUG_TYPE_ERROR)
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
}

GLFWwindow *testSetup(const int initWindowWidth, const int initWindowHeight, void(*windowHintFunction)())
{
    glfwSetErrorCallback(glfw_error_callback);
    if(glfwInit() == GLFW_FALSE)
    {
        std::fputs("GLFW initialization failed!\n", stderr);
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
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


    glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_error_callback, nullptr);


    return window;
}