#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"

class Model
{
public:
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	unsigned int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(unsigned int index_) const;
	GLuint GetShaderProgram() const;

	//glm::vec3 GetPosition() const; //gets position
	//float GetAngle() const; //gets angle
	//glm::vec3 GetRotation() const; //gets rotation
	//glm::vec3 GetScale() const; //gets scale

	//void SetPosition(glm::vec3 position_); //sets position
	//void SetAngle(float angle_); //sets angle
	//void SetRotation(glm::vec3 rotation_); //sets rotation
	//void SetScale(glm::vec3 scale_); //sets scale

private:
	glm::mat4 CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();

	std::vector<Mesh*> meshes;
	GLuint shaderProgram;

	//glm::vec3 position;
	//float angle;
	//glm::vec3 rotation;
	//glm::vec3 scale;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;
};

#endif;

