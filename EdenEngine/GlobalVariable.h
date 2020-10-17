// Eden Engine
/* Warning: These Varible (or object) will be called before "main()" hit, make sure their initialization 
(or Constructor) don't have some process what the main() must called */
#pragma once
#include <GLFW/glfw3.h>

#ifndef EDEN_GLOBAL_VARIABLE
#define EDEN_GLOBAL_VARIABLE

// GUI Style
/*******************************************************************************************************/
#define EDEN_GUI_CLASSIC 0
#define EDEN_GUI_DARK 1
#define EDEN_GUI_LIGHT 2
/*******************************************************************************************************/

// Screen and viewport
/*******************************************************************************************************/
GLFWwindow * editorWindow;
const char * editorFont = "Alibaba-PuHuiTi-Bold.ttf";
int ScreenWidth = 800;
int ScreenHeight = 600;
/*******************************************************************************************************/


#endif