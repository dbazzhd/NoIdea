#ifndef KEY_hpp
#define KEY_hpp

#include "mge\core\GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/config.hpp"

class Key : public GameObject {
public:
	Key(std::string pName, glm::vec3 pPosition, glm::vec3 pColor);
	~Key();
};


#endif
