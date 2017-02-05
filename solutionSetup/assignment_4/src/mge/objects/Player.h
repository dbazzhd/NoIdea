#ifndef PLAYER_hpp
#define PLAYER_hpp


#include "mge\core\GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"

#include "mge/config.hpp"

class Player : public GameObject {
public:
	Player(std::string pName, glm::vec3 pPosition, glm::vec3 pColor);
	~Player();
private:

};


#endif
