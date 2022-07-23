#include "Window.h"
#include "Debug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Windows.h>


static void GLFWErrorCallback(int error, const char* description)
{
	LOG("GLFW Error (%d) : %s \n", error, description);
}


Window::Window(uint32_t width, uint32_t height, bool vsync)
	: m_Width(width), m_Height(height), m_VSync(vsync)
{
	int status;

	status = glfwInit();
	ASSERT(status, "Failed to Initialize GLFW!\n");

	m_Window = glfwCreateWindow(m_Width, m_Height, "RayTracing", NULL, NULL);
	ASSERT(m_Window, "Failed to create GLFW window!\n");

	// Make maximized window
	RECT workArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
	glfwSetWindowPos(m_Window, workArea.left, workArea.top);
	glfwSetWindowSize(m_Window, workArea.right - workArea.left, workArea.bottom - workArea.top);

	glfwMakeContextCurrent(m_Window);

	status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(status, "Failed to Initialize glad!\n");

	LOG("OpenGL version: %s \n", glGetString(GL_VERSION));
	LOG("Graphics Card: %s \n", glGetString(GL_RENDERER));

	glfwSetErrorCallback(GLFWErrorCallback);
	if(m_VSync)
		glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_VSync = enabled;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}
