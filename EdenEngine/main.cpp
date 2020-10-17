// Eden Engine

#include <iostream>
#include <string>

#include "ComponentHeader/EdenCore.hpp"
#include "ComponentHeader/GlobalVariable.h"

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