#ifndef DOOR_HPP
#define DOOR_HPP

#include "mge\core\GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/config.hpp"

class Door : public GameObject {
public:
	Door(std::string pName, glm::vec3 pPosition, glm::vec3 pColor);
	~Door();
};



#endif
