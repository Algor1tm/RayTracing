// RayTracing.cpp : Defines the entry point for the application.
//

#include "RayTracing.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <ranges>

#include <ImGui/imgui.cpp>


using namespace std;

int main()
{
	glm::vec3 v(1);
	cout << "Hello CMake." << endl;

	if (glfwInit())
	{
		std::cout << "GLFW Succesfully initialized\n";
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "RayTracing", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (status)
	{
		std::cout << "glad Successfully initialized\n";
	}

	while (!glfwWindowShouldClose(window))
	{
		continue;
	}
	glfwTerminate();

	return 0;
}
