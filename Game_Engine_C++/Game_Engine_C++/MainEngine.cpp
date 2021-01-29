#include "MainEngine.h"

// because the unique pointer created is static we have to redeclare it at the top of the MainEngine cpp file - goes for any static variable
std::unique_ptr<MainEngine> MainEngine::engineInstance = nullptr;

MainEngine::MainEngine()
{
	// Sets default value for window and isRunning

	window = nullptr;
	isRunning = false;
}

MainEngine::~MainEngine()
{
}

// This is what will be called when I want to access anything from this class that is public
MainEngine* MainEngine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new MainEngine);
	}
	return engineInstance.get();
}

bool MainEngine::OnCreate(std::string name_, int width_, int height_)
{
	window = new Window(); // initialize window pointer

	if (!window->OnCreate(name_, width_, height_)) // calls Oncreate and check to see if return is true or false
	{
		std::cout << "Window failed to initialize" << std::endl;
		OnDestroy();

		return isRunning = false; // sets the isRunning variable to false then return the variable
	}
	return isRunning = true; // sets the isRunning variable to true then return the variable
}

void MainEngine::Run() // Entire Game loop of the engine, continously calling update and render
{
	while (isRunning)
	{
		Update(0.016f);
		Render();
	}
	//if (isRunning)
	//{
		OnDestroy();
	//}
}

bool MainEngine::GetIsRunning()
{
	return isRunning;
}

void MainEngine::Update(const float deltaTime_)
{
}

void MainEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // tells openGl what color to clear the screen with
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Call Game Render

	SDL_GL_SwapWindow(window->GetWindow()); // swap buffers
}

void MainEngine::OnDestroy()
{
	delete window; // cleaning up pointer - whenever cleaning up pointer delete window first then set to nullptr
	window = nullptr;
	SDL_Quit();
	exit(0);
}
