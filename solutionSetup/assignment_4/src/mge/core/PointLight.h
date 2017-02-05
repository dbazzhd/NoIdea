#ifndef PointLight_H
#define PointLight_H

#include "mge/core/Light.hpp"
#include <string>

#include <iostream>
#include <glm.hpp>

class PointLight : public Light {
public:

	PointLight(std::string pName, glm::vec3 pPosition, glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pLightColor, float pLightIntensity, float pLinearAttenuation, float pQuadraticAttenuation);
	
	~PointLight();
};



#endif
