#ifndef MAINENGINE_H
#define MAINENGINE_H

#include "Window.h"
#include <memory> // Gain access to smart pointers
#include "Timer.h"
#include "Debugger.h"
#include "GameInterface.h"
#include "Scene.h"
#include <string>

#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"

#include "../Camera/Camera.h"

class MainEngine
{
public:

	//Disables the creation of copy or move constructors - ensures that no objects are the same
	MainEngine(const MainEngine&) = delete;
	MainEngine(MainEngine&&) = delete;
	MainEngine& operator=(const MainEngine&) = delete;
	MainEngine& operator=(MainEngine&&) = delete;

	static MainEngine* GetInstance(); //returns a Main Engine Pointer - returns an instance or reference to this Main Engine object


	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();
	
	bool GetIsRunning() const;
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_); 
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

private:

	MainEngine(); //Move constructor and destructor to private to ensure another instance of the class cannot be created
	~MainEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<MainEngine> engineInstance; //Unique Pointer - holds a pointer to the object specified (MainEngine)
	friend std::default_delete<MainEngine>; // Unique pointer delete itself when the program ends and it is out of scope
											// Unlike normal pointers (have to be deleted manually) this deletes itself
											// default delete allows you to specify  how you want any object of type Main
											// enigne to be deleted
	Window* window;
	bool isRunning;
	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif

