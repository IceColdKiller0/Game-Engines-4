#ifndef GAME_1
#define GAME_1

#include "../Engine/Core/MainEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

class Game_1 : public GameInterface
{
public:
	Game_1();
	virtual ~Game_1();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};

#endif

