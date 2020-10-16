#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EditorGUI.hpp"

int ScreenWidth = 800;
int ScreenHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	// OpenGL Frame Init
	/*********************************************************************************************************/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(ScreenWidth, ScreenHeight, "EdenEngine", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	/*********************************************************************************************************/

	// Render Loop
	/*********************************************************************************************************/
	while (!glfwWindowShouldClose(window))
	{
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);



		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	/*********************************************************************************************************/

	glfwTerminate();
	return 0;
}