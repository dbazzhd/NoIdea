#ifndef SpotLight_H
#define SpotLight_H

#include "mge/core/Light.hpp"
#include <string>

#include <iostream>
#include <glm.hpp>

class SpotLight : public Light {
public:

	SpotLight(std::string pName, glm::vec3 pPosition, glm::vec3 pRotation, glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pLightColor, float pSpot, float pFalloff, float pLightIntensity, float pLinearAttenuation, float pQuadraticAttenuation);

	~SpotLight();
};



#endif
