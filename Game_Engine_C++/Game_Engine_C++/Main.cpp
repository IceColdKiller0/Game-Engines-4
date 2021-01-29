// #include "Engine/Core/MainEngine.h"
#include "MainEngine.h"

//MainEngine* engine;

int main(int argc, char* argv[])
{
	if (!MainEngine::GetInstance()->OnCreate("C++ Game Engine", 800, 600))
	{
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}
	MainEngine::GetInstance()->Run();
	return 0;
}


//#include "Window.h"
//
//Window* window;
//
//int main(int argc, char* argv[])
//{
//	window = new Window();
//
//	if (!window->OnCreate("C++ Game Engine", 800, 600))
//	{
//		delete window;
//		window = nullptr;
//		return 0;
//	}
//	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	SDL_GL_SwapWindow(window->GetWindow());
//	SDL_Delay(5000);
//	delete window;
//	window = nullptr;
//
//	return 0;
//}

//#include "Engine/Core/MainEngine.h"
//#include "MainEngine.h"
//
//MainEngine* engine;
//
//int main(int argc, char* argv[])
//{
	/*engine = new MainEngine();
	
	if (!engine->OnCreate("C++ Game Engine", 800, 600))
	{
		delete engine;
		engine = nullptr;
		return 0;
	}

	engine->Run();
	delete engine;
	engine = nullptr;
	return 0;*/
