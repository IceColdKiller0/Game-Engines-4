#include "Game_1.h"

Game_1::Game_1() : GameInterface() //declare constructor of parent class
{
    currentSceneNum = 0;
    currentScene = nullptr;
}

Game_1::~Game_1()
{
    delete currentScene;
    currentScene = nullptr;
}

bool Game_1::OnCreate()
{
    if (MainEngine::GetInstance()->GetCurrentScene() == 0)
    {
        currentScene = new StartScene();
        currentSceneNum = 0;
        return currentScene->OnCreate();
    }

    //std::cout << "Engine's scene is not initialized to 0" << std::endl;
    Debugger::FatalError("Engine's scene is not initialized to 0", "MainEngine.cpp ", __LINE__);
    return false;
}

void Game_1::Update(const float deltaTime_)
{
    if (currentSceneNum != MainEngine::GetInstance()->GetCurrentScene())
    {
        BuildScene();
    }

    currentScene->Update(deltaTime_);
}

void Game_1::Render()
{
    currentScene->Render();
}

void Game_1::BuildScene()
{
    delete currentScene;
    currentScene = nullptr;

    switch (MainEngine::GetInstance()->GetCurrentScene())
    {
    default: //case 0:
        currentScene = new StartScene();
        break;

    case 1:
        currentScene = new GameScene();
        break;
    }

    currentSceneNum = MainEngine::GetInstance()->GetCurrentScene(); // set game current scene # to engine scene #

    if (!currentScene->OnCreate()) //check to see if its false
    {
        //std::cout << "Scene failed to be created" << std::endl;
        Debugger::FatalError("Scene failed to be created", "MainEngine.cpp ", __LINE__);
        MainEngine::GetInstance()->Exit();
    }
}
