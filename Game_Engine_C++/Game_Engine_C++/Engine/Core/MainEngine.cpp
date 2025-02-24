#include "MainEngine.h"

// because the unique pointer created is static we have to redeclare it at the top of the MainEngine cpp file - goes for any static variable
std::unique_ptr<MainEngine> MainEngine::engineInstance = nullptr;

MainEngine::MainEngine()
{
	// Sets default value for window and isRunning

	window = nullptr;
	isRunning = false;
	fps = 60;
	gameInterface = nullptr;
	camera = nullptr;
	currentSceneNum = 0;
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
	Debugger::OnCreate();
	window = new Window(); // initialize window pointer

	if (!window->OnCreate(name_, width_, height_)) // calls Oncreate and check to see if return is true or false
	{
		//std::cout << "Window failed to initialize" << std::endl; //fatal error
		Debugger::FatalError("Failed to initialize Window", "MainEngine.cpp ", __LINE__);
		OnDestroy();

		return isRunning = false; // sets the isRunning variable to false then return the variable
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	if (gameInterface)
	{
		if (!gameInterface->OnCreate())
		{
			//std::cout << "Game failed to initialize" << std::endl;
			Debugger::FatalError("Failed to initialize Game", "MainEngine.cpp ", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	Debugger::Info("Everything worked ", "MainEngine.cpp " /*__FILE__*/, __LINE__);
	timer.Start(); // starts timer
	return isRunning = true; // sets the isRunning variable to true then return the variable
}

void MainEngine::Run() // Entire Game loop of the engine, continously calling update and render
{
	while (isRunning)
	{
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	//if (isRunning)
	//{
		OnDestroy();
	//}
}

void MainEngine::Exit()
{
	isRunning = false;
}

bool MainEngine::GetIsRunning() const
{
	return isRunning;
}

int MainEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float MainEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float MainEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* MainEngine::GetCamera() const
{
	return camera;
}

void MainEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void MainEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void MainEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void MainEngine::NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_)
{
}

void MainEngine::NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void MainEngine::NotifyOfMouseMove(glm::ivec2 mouse_)
{
	if (camera)
	{
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void MainEngine::NotifyOfMouseScroll(int y_)
{
	if (camera)
	{
		camera->ProcessMouseZoom(y_);
	}
}

void MainEngine::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
		//std::cout << deltaTime_ << std::endl;
	}
	
}

void MainEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // tells openGl what color to clear the screen with
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Call Game Render
	if (gameInterface)
	{
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow()); // swap buffers
}

void MainEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	
	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window; // cleaning up pointer - whenever cleaning up pointer delete window first then set to nullptr
	window = nullptr;
	SDL_Quit();
	exit(0);
}
