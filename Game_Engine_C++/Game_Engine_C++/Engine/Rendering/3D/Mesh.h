#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector> // dynamically sized array
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"

struct Vertex //non-interleaved
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates; // what place on a 2d image does this vertex takes its texture info from
	glm::vec3 colour; // can be a vec4 which inlcudes alpha
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertexList_, GLuint shaderProgram_); // takes in a vector of type vertex objects // pass in the vector by reference (&) than the value, saves computation time
	~Mesh();

	void Render(Camera* camera_, glm::mat4 transform_);

private:
	void GenerateBuffers(); //sets up VAO and VBO
	GLuint VAO, VBO; 
	std::vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc; //uniform location variable

	//Vertex Array Object (VAO) states to the GPU how we store our vertex data
	//Vertex Buffer Object (VBO) is an object buffer that provides the methods to push data to the GPU
	//VBO contains all the vertex data in it and VAO tells the GPU how everything is separated in memory
	//uniform is a variable in our shaderprogram
};

#endif;

