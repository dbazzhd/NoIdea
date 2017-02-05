#include "mge/objects/Coin.h"

Coin::Coin(std::string pName, glm::vec3 pPosition, glm::vec3 pColor) : GameObject(pName, pPosition) {
	setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_unity.obj"));
	setMaterial(new ColorMaterial(pColor));
	setTransform(glm::translate(pPosition));
	std::cout << " SDADSADASDSAD " << std::endl;
}
Coin::~Coin() {

}