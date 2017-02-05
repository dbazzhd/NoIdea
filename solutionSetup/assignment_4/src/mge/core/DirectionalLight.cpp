#include "mge/core/DirectionalLight.h"
#include "mge/core/Light.hpp"
#include "mge/core/GameObject.hpp"

using namespace std;


DirectionalLight::DirectionalLight(std::string pName = "light", glm::vec3 pPosition = glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3 pRotation = glm::vec3(0,0,0), glm::vec3 pScale = glm::vec3(1,1,1),
	glm::vec3 pAmbientColor = glm::vec3(0.5f, 0.5f, 0.5f), float pAmbientIntensity = 0.1f, glm::vec3 pLightColor = glm::vec3(1, 1, 1), float pLightIntensity = 1.0f)
	: Light(pName, pPosition, pAmbientColor, pAmbientIntensity, pLightColor, 1, 0, 0, pLightIntensity, 0, 0)
{
	// ---------------------------------------------------
	rotate(glm::radians(pRotation.z), glm::vec3(0, 0, 1));
	rotate(glm::radians(pRotation.x), glm::vec3(1, 0, 0));
	rotate(glm::radians(pRotation.y), glm::vec3(0, 1, 0));
	// ---------------------------------------------------
	scale(pScale);
}

DirectionalLight::~DirectionalLight()
{
	//dtor
}



