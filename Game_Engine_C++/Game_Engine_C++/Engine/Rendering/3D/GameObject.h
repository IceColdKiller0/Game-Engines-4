#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_);
	GameObject(Model* model_, glm::vec3 position_);
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const; //gets position
	float GetAngle() const; //gets angle
	glm::vec3 GetRotation() const; //gets rotation
	glm::vec3 GetScale() const; //gets scale
	std::string GetTag() const; //gets tag

	void SetPosition(glm::vec3 position_); //sets position
	void SetAngle(float angle_); //sets angle
	void SetRotation(glm::vec3 rotation_); //sets rotation
	void SetScale(glm::vec3 scale_); //sets scale
	void SetTag(std::string tag_); //sets tag

private:
	Model* model;
	unsigned int modelInstance;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::string tag; 
};

#endif;

