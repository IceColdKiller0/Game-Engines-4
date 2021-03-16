#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPos_, float ambValue_, float diffValue_, float specValue_, glm::vec3 lightColour_)
{
    lightPos = glm::vec3();
    ambValue = 0.0f;
    diffValue = 0.0f;
    specValue = 0.0f;
    lightColour = glm::vec3();

    lightPos = lightPos_;
    ambValue = ambValue_;
    diffValue = diffValue_;
    specValue = specValue_;
    lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition()
{
    return lightPos;
}

float LightSource::GetAmbValue()
{
    return ambValue;
}

float LightSource::GetDiffValue()
{
    return diffValue;
}

float LightSource::GetSpecValue()
{
    return specValue;
}

glm::vec3 LightSource::GetLightColour()
{
    return lightColour;
}

void LightSource::SetPosition(glm::vec3 lightPos_)
{
    lightPos = lightPos_;
}

void LightSource::SetAmbValue(float ambValue_)
{
    ambValue = ambValue_;
}

void LightSource::SetDiffValue(float diffValue_)
{
    diffValue = diffValue_;
}

void LightSource::SetSpecValue(float specValue_)
{
    specValue = specValue_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
    lightColour = lightColour_;
}
