#include "GameScene.h"

GameScene::GameScene()
{
	shape = nullptr;
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	std::cout << "Game Scene Loaded" << std::endl;
	Debugger::Info("Game Scene Loaded ", "MainEngine.cpp ", __LINE__);

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f); //top left
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f); //bottom left
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f); //bottom right
	vertexList.push_back(v);

	Vertex v2;
	std::vector<Vertex> vertexList2;
	vertexList2.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f); //top left
	vertexList2.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.0f); //top right
	vertexList2.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f); //bottom right 
	vertexList2.push_back(v);

	
	Model* square = new Model();
	square->AddMesh(new Mesh(vertexList));
	square->AddMesh(new Mesh(vertexList2));
	shape = new GameObject(square);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	std::cout << deltaTime_ << std::endl;
}

void GameScene::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shape->Render();
}
