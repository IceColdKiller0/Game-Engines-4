#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

class Model
{
public:
	Model(GLuint shaderProgram_, glm::vec3 position_ = glm::vec3(),
		float angle_ = 0.0f, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 scale_ = glm::vec3(1.0f));
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);


	glm::vec3 GetPosition() const; //gets position
	float GetAngle() const; //gets angle
	glm::vec3 GetRotation() const; //gets rotation
	glm::vec3 GetScale() const; //gets scale

	void SetPosition(glm::vec3 position_); //sets position
	void SetAngle(float angle_); //sets angle
	void SetRotation(glm::vec3 rotation_); //sets rotation
	void SetScale(glm::vec3 scale_); //sets scale

private:
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 GetTransform() const;
};

#endif;

