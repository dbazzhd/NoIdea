#ifndef CAMERAFOLLOWBEHAVIOUR_HPP
#define CAMERAFOLLOWBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"

class CameraFollowBehaviour : public AbstractBehaviour {
public:
	CameraFollowBehaviour(GameObject * pTarget);
	~CameraFollowBehaviour();

	virtual void update(float pStep);
private:
	GameObject* _target;
};


#endif
