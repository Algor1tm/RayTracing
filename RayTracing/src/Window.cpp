#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


static void GLFWErrorCallback(int error, const char* description)
{
	std::cout << "GLFW Error (" << error << ">: " << description << "\n";
}


Window::Window(uint32_t width, uint32_t height, bool vsync)
	: m_Width(width), m_Height(height), m_VSync(vsync)
{
	if (!glfwInit())
	{
		std::cout << "Failed to Initialize GLFW!\n";
		return;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, "RayTracing", NULL, NULL);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to create GLFW window!\n";
		return;
	}

	glfwMakeContextCurrent(m_Window);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status == NULL)
	{
		std::cout << "Failed to Initialize glad!\n";
		return;
	}

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
