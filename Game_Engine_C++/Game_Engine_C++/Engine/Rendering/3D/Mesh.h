#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector> // dynamically sized array
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex //non-interleaved
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates; // what place on a 2d image does this vertex takes its texture info from
	glm::vec3 colour; // can be a vec4 which inlcudes alpha
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_); // takes in a vector of type vertex objects // pass in the vector by reference (&) than the value, saves computation time
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4>& instances_);

private:
	void GenerateBuffers(); //sets up VAO and VBO
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint viewPos, lightPos;
	GLuint ambValue, diffValue, specValue, lightColour;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc; //uniform location variable
	GLuint diffuseMapLoc, shininessLoc, transparencyLoc, ambientLoc, diffuseLoc, specularLoc;

	//Vertex Array Object (VAO) states to the GPU how we store our vertex data
	//Vertex Buffer Object (VBO) is an object buffer that provides the methods to push data to the GPU
	//VBO contains all the vertex data in it and VAO tells the GPU how everything is separated in memory
	//uniform is a variable in our shaderprogram
};

#endif;

