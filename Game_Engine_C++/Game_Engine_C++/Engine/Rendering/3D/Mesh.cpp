#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint shaderProgram_)
{
	VAO = 0;
	VBO = 0;
	vertexList = std::vector<Vertex>(); //sets vertex list to equal an empty vector
	shaderProgram = 0;
	vertexList = vertexList_; //sets the class vertex list vector equal to the vertex list passed in as a param 
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO); //Deletes VAO - opengl has its own way of deleting
	glDeleteBuffers(1, &VBO); //Deletes VBO

	vertexList.clear();
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_)
{
	glBindVertexArray(VAO); //BIND VAO

	glEnable(GL_DEPTH_TEST); // when objects are rendered their z values will be taken into consideration

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glDrawArrays(GL_TRIANGLES, 0, vertexList.size()); //draw

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO); //Generate VAO
	glGenBuffers(1, &VBO); //Generate VBO
	glBindVertexArray(VAO); //Bind to the GPU as an array
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind to the GPU 
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
}
