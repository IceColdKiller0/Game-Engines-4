#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	std::cout << "\nStart Scene" << std::endl;
	Debugger::Info("Start Scene ", "MainEngine.cpp ", __LINE__);

	std::cout << "\nNow entering the Game Scene. Please Wait...\n" << std::endl;
	Debugger::Info("Now entering the Game Scene. Please Wait... ", "MainEngine.cpp ", __LINE__);
	SDL_Delay(3000);
	MainEngine::GetInstance()->SetCurrentScene(1); // switching scene to Game Scene
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
