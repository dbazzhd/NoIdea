#ifndef COIN_hpp
#define COIN_hpp

#include "mge\core\GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/config.hpp"

class Coin : public GameObject {
public:
	Coin(std::string pName, glm::vec3 pPosition, glm::vec3 pColor);
	~Coin();
};


#endif
