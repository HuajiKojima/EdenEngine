// Eden Engine
#pragma once
#ifndef EDEN_EDITOR_GUI
#define EDEN_EDITOR_GUI

#include "DevelopmentKit/ImGui/imgui.h"
#include "DevelopmentKit/ImGui/imgui_impl_glfw.h"
#include "DevelopmentKit/ImGui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#define EDEN_GUI_CLASSIC 0
#define EDEN_GUI_DARK 1
#define EDEN_GUI_LIGHT 2


namespace EDEN 
{
	void GUIInit(GLFWwindow *window, int editorStyle, const char *editorFont);
	void GUINewFrame();
	void GUIRender();
	void GUIShutdown();

	void GUIInit(GLFWwindow *window, int editorStyle, const char *editorFont)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO & io = ImGui::GetIO();
		(void)io;
		io.Fonts->AddFontFromFileTTF(editorFont, 24.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		// Init Editor Style
		//-----------------------------------------------------------------------------------------------
		switch (editorStyle)
		{
		case EDEN_GUI_CLASSIC:
			ImGui::StyleColorsClassic();
			break;
		case EDEN_GUI_DARK:
			ImGui::StyleColorsDark();
			break;
		case EDEN_GUI_LIGHT:
			ImGui::StyleColorsLight();
			break;
		default:
			// Throw the exception
			break;
		}
		//-----------------------------------------------------------------------------------------------
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void GUINewFrame() 
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUIRender() 
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUIShutdown() 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
#endif