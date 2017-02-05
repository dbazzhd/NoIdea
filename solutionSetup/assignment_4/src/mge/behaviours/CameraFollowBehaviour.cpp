#include "mge/behaviours/CameraFollowBehaviour.h"

CameraFollowBehaviour::CameraFollowBehaviour(GameObject * pTarget) : AbstractBehaviour(), _target(pTarget) {
	_target = pTarget;
}
CameraFollowBehaviour::~CameraFollowBehaviour() {

}

void CameraFollowBehaviour::update(float pStep) {
	glm::vec3 target = _target->getWorldPosition();
	glm::vec3 owner = _owner->getWorldPosition();
	glm::vec3 position = glm::vec3(target.x, owner.y, target.z);
	// Prerobi na setRotation(Camera);
	glm::mat4 matrix(glm::translate(position) *glm::rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0)));
	_owner->setTransform(matrix);
}