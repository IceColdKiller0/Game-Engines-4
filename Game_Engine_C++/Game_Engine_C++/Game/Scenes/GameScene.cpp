#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	std::cout << "Game Scene" << std::endl;
	Debugger::Info("Game Scene ", "MainEngine.cpp ", __LINE__);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
}
