#include "mge/behaviours/CameraOrbit.h"
#include "mge/core/Gameobject.hpp"
#include <cmath>

#include <iostream>
using namespace std;

CameraOrbit::CameraOrbit(GameObject * pTarget, sf::Window * pWindow, float pDistance, sf::Vector2f pMaxTiltX, float pYRotationSpeed)
	: AbstractBehaviour(), _target(pTarget) {
	_window = pWindow;
	_distance = pDistance;
	_maxTiltX = pMaxTiltX;
	_yRotationSpeed = pYRotationSpeed;

}
CameraOrbit::~CameraOrbit() {

}
void CameraOrbit::update(float pStep) {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
	// ranges from -0.5 to 0.5
	sf::Vector2f mPos = sf::Vector2f((mousePosition.x - 400.0f) / 800.0f, (mousePosition.y - 300.0f) / -600.0f);
	float border = 0.125f;

	yRot = (mPos.x <= -border) ? yRot - _yRotationSpeed : ((mPos.x >= border) ? yRot + _yRotationSpeed : yRot);
	xRot = (mPos.y <= -border && xRot < _maxTiltX.y) ? xRot + 1 : ((mPos.y >= border && xRot > _maxTiltX.x) ? xRot - 1 : xRot);

	//                           Rotation around Y axis                    Rotation around X axis                                 Translation
	glm::mat4 matrix(glm::translate(_target->getWorldPosition()) * glm::rotate(glm::radians(yRot), glm::vec3(0, 1, 0)) * glm::rotate(glm::radians(xRot), glm::vec3(1, 0, 0)) *  glm::translate(glm::vec3(0, 0, _distance)));
	_owner->setTransform(matrix);
	_owner->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	//Debug(_owner->getWorldPosition());
}
void CameraOrbit::Debug(glm::vec3 pPosition) {
	cout << pPosition[0] << ":" << pPosition[1] << ":" << pPosition[2] << endl;
}