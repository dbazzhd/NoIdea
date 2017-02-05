#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "mge/core/GameObject.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world to view matrix by taking the inverse of the camera transform
 * (see renderer).
 */
class Light : public GameObject
{
	public:
	    //Light(std::string pName, glm::vec3 pPosition);
		Light(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pLightColor, int pType, float pSpotAngle, float pFallAngle, float pLightIntensity, float pLinearAttenuation, float pQuadraticAttenuation);

		virtual ~Light();

		glm::vec3 getAmblientColor();
		glm::vec3 getGlobalAmbient();
		float getAmbientIntensity();
		glm::vec3 getLightColor();
		int getType();
		float getSpotAngle();
		float getFallAngle();
		float getLightIntensity();
		float getLinearAttenuation();
		float getQuadraticAttenuation();
	protected:
		float _spotAngle;
		float _fallAngle;
		int _lightType;
		glm::vec3 _ambientColor;
		float _ambientIntensity;
		glm::vec3 _globalAmbient;

		glm::vec3 _lightColor;
		float _lightIntensity;
		float _linearAttenuation;
		float _quadraticAttenuation;
};

#endif // LIGHT_H
