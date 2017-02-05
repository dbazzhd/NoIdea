#include "mge/behaviours/CollisionResolver.h"


CollisionResolver::CollisionResolver(World * pWorld) {
	_world = pWorld;
}
CollisionResolver::~CollisionResolver() {

}

void CollisionResolver::CheckCollisions() {
	for (int a = 0; a < _world->getChildCount()-1; a++) {
		for (int b = a + 1; b < _world->getChildCount(); b++) {
			RadialHitTest(_world->getChildAt(a), _world->getChildAt(b));
		}
	}
}

void CollisionResolver::RadialHitTest(GameObject * pA, GameObject * pB) {
	if (glm::distance(pA->getWorldPosition(), pB->getWorldPosition()) < 1) {
		LuaParser::Instance()->PushCollisionData(pA->getCollisionFunction(pB->getObjectType()), pA, pB);
	}
}
