#ifndef CameraOrbit_hpp
#define CameraOrbit_hpp

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm\glm.hpp"
#include "SFML\window.hpp"

class CameraOrbit : public AbstractBehaviour {
public:
	CameraOrbit(GameObject * pTarget, sf::Window * pWindow, float pDistance, sf::Vector2f pMaxTiltX, float pYRotationSpeed);
	~CameraOrbit();
	virtual void update(float pStep);
	void Debug(glm::vec3 pPosition);
private:
	sf::Window * _window;
	GameObject * _target;
	float yRot = 0;
	float xRot = 0;
	float _distance;
	sf::Vector2f _maxTiltX;
	float _yRotationSpeed;
};

#endif
