#ifndef WALL_HPP
#define WALL_HPP

#include "mge\core\GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/config.hpp"

class Wall : public GameObject {
public:
	Wall(std::string pName, glm::vec3 pPosition, glm::vec3 pColor);
	~Wall();
};


#endif
