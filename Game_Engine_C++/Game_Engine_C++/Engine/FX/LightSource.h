#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glew.h>
#include <vector> // dynamically sized array
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 lightPos_, float ambValue_, float diffValue_, float specValue_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition();
	float GetAmbValue();
	float GetDiffValue();
	float GetSpecValue();
	glm::vec3 GetLightColour();

	void SetPosition(glm::vec3 lightPos_); //sets position
	void SetAmbValue(float ambValue_); //sets ambvalue
	void SetDiffValue(float diffValue_); //sets diffvalue
	void SetSpecValue(float specValue_); //sets specvalue
	void SetLightColour(glm::vec3 lightColour_); //sets lightcolour

private:
	glm::vec3 lightPos;
	float ambValue;
	float diffValue;
	float specValue;
	glm::vec3 lightColour;
};

#endif // !LIGHTSOURCE_H


