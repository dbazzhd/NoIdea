#include "mge/core/PointLight.h"
#include "mge/core/Light.hpp"
#include "mge/core/GameObject.hpp"

using namespace std;

PointLight::PointLight(std::string pName = "light", glm::vec3 pPosition = glm::vec3(0.0f, 5.0f, 0.0f),
	glm::vec3 pAmbientColor = glm::vec3(0.5f, 0.5f, 0.5f), float pAmbientIntensity = 0.1f, glm::vec3 pLightColor = glm::vec3(1, 1, 1), float pLightIntensity = 1.0f, float pLinearAttenuation = 0.0f, float pQuadraticAttenuation = 0.0f)
	: Light(pName, pPosition, pAmbientColor, pAmbientIntensity, pLightColor, 2, 0, 0, pLightIntensity, pLinearAttenuation, pQuadraticAttenuation) 
{

}

PointLight::~PointLight()
{

}