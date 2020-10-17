// Eden Engine
// Eden Engine Core
#pragma once
#ifndef EDEN_CORE
#define EDEN_CORE

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ComponentHeader/EditorGUI.hpp"
#include "ComponentHeader/GlobalVariable.h"

namespace EDEN 
{
	class CoreExecption 
	{
	private:
		std::string exceptionReason;
	public:
		CoreExecption(std::string & reason)
		{
			this->exceptionReason = reason;
		}

		std::string exceptionPrint() 
		{
			return exceptionReason;
		}
	};

	std::string exceptionReason;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	GLFWwindow * EdenInit()
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
			glfwTerminate();
			exceptionReason = "Failed to create GLFW window";
			CoreExecption CE(exceptionReason);
			throw CE;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			exceptionReason = "Failed to initialize GLAD";
			CoreExecption CE(exceptionReason);
			throw CE;
		}
		/*********************************************************************************************************/
		
		// Editor GUI init
		GUIInit(window, EDEN_GUI_DARK, editorFont);

		return window;
	}

	void EdenRender(GLFWwindow * window) 
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			GUINewFrame();

			// Render Process
			//---------------------------------------------------------------------

			//---------------------------------------------------------------------

			GUIRender();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		return;
	}

	void EdenShutdown() 
	{
		GUIShutdown();
		glfwTerminate();
	}
}


#endif