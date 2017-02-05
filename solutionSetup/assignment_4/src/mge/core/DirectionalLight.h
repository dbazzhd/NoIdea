#ifndef DirectionalLight_H
#define DirectionalLight_H

#include "mge/core/Light.hpp"
#include <string>

#include <iostream>
#include <glm.hpp>
using namespace std;


/**
* Camera is just a GameObject with an additional projection matrix.
* The camera's own transform is used to generate a world to view matrix by taking the inverse of the camera transform
* (see renderer).
*/
class DirectionalLight : public Light
{
public:
	DirectionalLight(std::string pName, glm::vec3 pPosition, glm::vec3 pRotation, glm::vec3 pScale, glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pLightColor, float pLightIntensity);

	virtual ~DirectionalLight();
private:
};

#endif