#include <iostream>
using namespace std;

#include <glm.hpp>
#include "mge/core/Light.hpp"

/*Light::Light(std::string pName = "light", glm::vec3 pPosition = glm::vec3(0,0,0)) : GameObject(pName, pPosition) {

}*/

Light::Light(std::string pName = "light", glm::vec3 pPosition = glm::vec3(0.0f, 5.0f, 0.0f),
	glm::vec3 pAmbientColor = glm::vec3(0.5f, 0.5f, 0.5f), float pAmbientIntensity = 0.1f, glm::vec3 pLightColor = glm::vec3(1, 1, 1), int pType = 2, float pSpotAngle = 45.0f, float pFallAngle = 0.0f, float pLightIntensity = 1.0f, float pLinearAttenuation = 0.0f, float pQuadraticAttenuation = 0.0f)
:	GameObject(pName, pPosition)
{
	_quadraticAttenuation = pQuadraticAttenuation;
	_linearAttenuation = pLinearAttenuation;
	_lightIntensity = pLightIntensity;
	_fallAngle = pFallAngle;
	_spotAngle = pSpotAngle;
	_lightType = pType;
	_ambientColor = pAmbientColor;
	_globalAmbient = pAmbientColor*pAmbientIntensity;
	_ambientIntensity = pAmbientIntensity;
	_lightColor = pLightColor;
}

Light::~Light()
{
	//dtor
}

glm::vec3 Light::getAmblientColor() {
	return _ambientColor;
}

glm::vec3 Light::getGlobalAmbient() {
	return _globalAmbient;
}

float Light::getAmbientIntensity() {
	return _ambientIntensity;
}

glm::vec3 Light::getLightColor() {
	return _lightColor;
}
int Light::getType() {
	return _lightType;
}
float Light::getSpotAngle() {
	return _spotAngle;
}
float Light::getFallAngle() {
	return _fallAngle;
}
float Light::getLightIntensity() {
	return _lightIntensity;
}
float Light::getLinearAttenuation() {
	return _linearAttenuation;
}
float Light::getQuadraticAttenuation() {
	return _quadraticAttenuation;
}


