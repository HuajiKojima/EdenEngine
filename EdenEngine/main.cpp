// Eden Engine

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EdenCore.hpp"
#include "GlobalVariable.h"

int main()
{
	try
	{
		editorWindow = EDEN::EdenInit();
	}
	catch (EDEN::CoreExecption &e)
	{
		std::cout << "EDEN::ERROR::CORE::" << e.exceptionPrint() << std::endl;
		return -1;
	}
	EDEN::EdenRender(editorWindow);
	EDEN::EdenShutdown();
	return 0;
}