#include "mge/core/SpotLight.h"
#include "mge/core/Light.hpp"
#include "mge/core/GameObject.hpp"

using namespace std;

SpotLight::SpotLight(std::string pName = "light", glm::vec3 pPosition = glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3 pRotation = glm::vec3(0,0,0),
	glm::vec3 pAmbientColor = glm::vec3(0.5f, 0.5f, 0.5f), float pAmbientIntensity = 0.1f, glm::vec3 pLightColor = glm::vec3(1, 1, 1), float pLightIntensity = 1.0f, float pSpot = 90.0f, float pFalloff = 0.0f, float pLinearAttenuation = 0, float pQuadraticAttenuation = 0)
	: Light(pName, pPosition, pAmbientColor, pAmbientIntensity, pLightColor, 3, pSpot, pFalloff, pLightIntensity, pLinearAttenuation, pQuadraticAttenuation)
{
	// ---------------------------------------------------
	rotate(glm::radians(pRotation.z), glm::vec3(0, 0, 1));
	rotate(glm::radians(pRotation.x), glm::vec3(1, 0, 0));
	rotate(glm::radians(pRotation.y), glm::vec3(0, 1, 0));
	// ---------------------------------------------------
}

SpotLight::~SpotLight()
{

}