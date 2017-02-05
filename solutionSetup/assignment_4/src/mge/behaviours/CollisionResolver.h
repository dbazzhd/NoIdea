#ifndef COLLISIONRESOLVER_hpp
#define COLLISIONRESOLVER_hpp

#include <cassert>
#include <vector>
#include "mge/core/LuaParser.hpp"

class CollisionResolver {
public:
	CollisionResolver(World * pWorld);
	~CollisionResolver();

	void CheckCollisions();
private:
	void RadialHitTest(GameObject* pA, GameObject * pB);
	World* _world;
};

#endif
