
#ifndef LuaParser_hpp
#define LuaParser_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "lua.hpp"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/objects/Player.h"
#include "mge/objects/Key.h"
#include "mge/objects/Coin.h"
#include "mge/objects/Door.h"
#include "mge/objects/Wall.h"

#include "mge/objects/TextField.h"


#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraFollowBehaviour.h"
#include "mge/behaviours/CameraOrbit.h"

//#include "mge/behaviours/CollisionResolver.h"

#include "glm.hpp"


//using namespace std;

//------------------------------------------------------------------------------------------------------------
//                                                      LuaParser
//------------------------------------------------------------------------------------------------------------
class LuaParser {
    
public:
	LuaParser(sf::RenderWindow * pWindow, World * pWorld);
	static LuaParser * Instance();
	void Step();
	World* getWorld();
	char* currentFunction;
	void PushCollisionData(std::string pFunction, GameObject* pA, GameObject * pB);

	glm::vec3 GetColor(std::string pColor);
	int GetObjectType(std::string pName);
	void CreateGameObject(GameObject * pGameObject, int pObjectType);
	void AddTextField(TextField * pTextField);

	int IDNameCount();
	void RegisterObjectName(int pIndex, std::string pName);


	lua_State * lua;
	sf::RenderWindow * window;
	bool clickedLeft = false;

	void RenderTextFields();
private:
	void Load();
	void Setup();


	World* _world;
	vector<TextField*> _textFields;

	std::map<std::string, int> _idNamePair;

};

#endif
