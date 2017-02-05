

#include "LuaParser.hpp"
//#include "include\lua.h"
#include "lua.hpp"
#include "mge/config.hpp"
LuaParser * parser;

std::map<std::string, sf::Texture*> imageCache;
int idCount = 0;
LuaParser* LuaParser::Instance() {
	return parser;
}
World* LuaParser::getWorld() {
	return _world;
}
int LuaParser::IDNameCount() {
	return _idNamePair.size();
}
//------------------------------------------------------------------------------------------------------------
//                                                      RegisterObjectName()
//------------------------------------------------------------------------------------------------------------
void LuaParser::RegisterObjectName(int pIndex, std::string pName) {
	_idNamePair[pName] = pIndex+1;

}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: saveObjectName()
//------------------------------------------------------------------------------------------------------------
int registerObjectName(lua_State* pLua) {
	std::string name = lua_tostring(pLua, -1);
	parser->RegisterObjectName(idCount, name);
	std::cout << "LuaParser: " << name << " :Registered" << std::endl;
	idCount += 1;
	return 0;
}


//------------------------------------------------------------------------------------------------------------
//                                                      Lua: say(string)
//------------------------------------------------------------------------------------------------------------
int say(lua_State * lua) {
	if (lua_isstring(lua, -1)) {
		std::cout << lua_tostring(lua, -1) << std::endl; //read 1st parameter as a string
	}
	return 0; //function returns nothing to lua (=void)
}

//------------------------------------------------------------------------------------------------------------
//                                                      Lua: visit()
//------------------------------------------------------------------------------------------------------------
int visit(lua_State * lua) {
	char* functionName = (char*)lua_tostring(lua, -1);
	parser->currentFunction = functionName;
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      PushCollisionData()
//------------------------------------------------------------------------------------------------------------
void LuaParser::PushCollisionData(std::string pFunction, GameObject* pA, GameObject * pB) {
	if (pFunction == "") return;
	char* functionName = &pFunction[0];
	lua_getglobal(lua, functionName);
	if (lua_isnil(lua, -1)) { //if is doesn't exist, bail out
		lua_settop(lua, 0); //clear lua stack to avoid overflow
		std::cout << "LuaParser: " << pFunction << " :Does not exist" << std::endl;
		return;
	}
	std::cout << "LuaParser: " << pA->getName() << " of type: " << pA->getObjectType() << " Collided with: " << pB->getName() << " of type: " << pB->getObjectType() << std::endl;
	lua_pushlightuserdata(lua, pA);
	lua_pushlightuserdata(lua, pB);

	lua_pcall(lua, 2, 0, 0);
	

}
//------------------------------------------------------------------------------------------------------------
//                                                      Step()
//------------------------------------------------------------------------------------------------------------
void LuaParser::Step() {
	lua_getglobal(lua, currentFunction); //get function
	if (lua_isnil(lua, -1)) { //if is doesn't exist, bail out
		lua_settop(lua, 0); //clear lua stack to avoid overflow
		return;
	}
	lua_pcall(lua, 0, 0, 0); //call function
}
//------------------------------------------------------------------------------------------------------------
//                                                      GetObjectType()
//------------------------------------------------------------------------------------------------------------
int LuaParser::GetObjectType(std::string pName) {
	if (pName == "player") return config::TYPE_Player;
	if (pName == "key") return config::TYPE_Key;
	if (pName == "coin") return config::TYPE_Coin;
	if (pName == "door") return config::TYPE_Door;
	if (pName == "wall") return config::TYPE_Wall;
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      GetColor()
//------------------------------------------------------------------------------------------------------------
glm::vec3 LuaParser::GetColor(std::string pColor) {
	if (pColor == "black") return glm::vec3(0, 0, 0);
	if (pColor == "red") return glm::vec3(1, 0, 0);
	if (pColor == "green") return glm::vec3(0, 1, 0);
	if (pColor == "blue") return glm::vec3(0, 0, 1);
	if (pColor == "gray" || pColor == "grey") return glm::vec3(0.5f, 0.5f, 0.5f);
	if (pColor == "brown") return glm::vec3(0.55f, 0.27f, 0.07f);
	if (pColor == "ltgreen") return glm::vec3(0.48f, 0.98f, 0.0f);
	if (pColor == "yellow") return glm::vec3(1.0f, 1.0f, 0.0f);
	if (pColor == "purple") return glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::vec3(1,1,1);
}

//------------------------------------------------------------------------------------------------------------
//                                                      CreateGameObject()
//------------------------------------------------------------------------------------------------------------
void LuaParser::CreateGameObject(GameObject * pGameObject, int pObjectType) {
		pGameObject->setObjectType(pObjectType);
		if (pGameObject->getObjectType() == 0) {
			pGameObject->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_unity.obj"));
			pGameObject->setMaterial(new ColorMaterial(glm::vec3(1, 1, 1)));
		}
		parser->getWorld()->add(pGameObject);
		std::cout << "LuaParser: " << pGameObject->getName() << "  |  " << pGameObject->getObjectType() << " :Created" << std::endl;
		lua_pushlightuserdata(lua, pGameObject);
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: importObject(name, x, y, z, color)
//------------------------------------------------------------------------------------------------------------
int importObject(lua_State* pLua) {
	std::string name = lua_isstring(pLua, -5) ? lua_tostring(pLua, -5) : "Name error";
	float x = lua_isnumber(pLua, -4) ? lua_tonumber(pLua, -4) : 0.0f;
	float y = lua_isnumber(pLua, -3) ? lua_tonumber(pLua, -3) : 0.0f;
	float z = lua_isnumber(pLua, -2) ? lua_tonumber(pLua, -2) : 0.0f;
	glm::mat4 matrix = glm::translate(glm::vec3(-x, y, z));

	glm::vec3 color = parser->GetColor(lua_isstring(pLua, -1) ? lua_tostring(pLua, -1) : "Color error");

	parser->CreateGameObject(new GameObject(name, glm::vec3(x, y, -z)), 0);
	return 0;
}
int createObject(lua_State * pLua) {
	std::string name = lua_isstring(pLua, -5) ? lua_tostring(pLua, -5) : "Name error";
	float x = lua_isnumber(pLua, -4) ? lua_tonumber(pLua, -4) : 0.0f;
	float y = lua_isnumber(pLua, -3) ? lua_tonumber(pLua, -3) : 0.0f;
	float z = lua_isnumber(pLua, -2) ? lua_tonumber(pLua, -2) : 0.0f;
	glm::mat4 matrix = glm::translate(glm::vec3(-x, y, z));

	glm::vec3 color = parser->GetColor(lua_isstring(pLua, -1) ? lua_tostring(pLua, -1) : "Color error");

	switch (parser->IDNameCount()) {
	case 0:
		// WRONG NAME
		parser->CreateGameObject(new GameObject(name, glm::vec3(x, y, -z)), 0);
		break;
		// PLAYER
	case config::TYPE_Player:
		parser->CreateGameObject(new Player(name, glm::vec3(x, y, -z), color), parser->GetObjectType(name));
		break;
		// KEY
	case config::TYPE_Key:
		parser->CreateGameObject(new Key(name, glm::vec3(x, y, -z), color), parser->GetObjectType(name));
		break;
		// COIN
	case config::TYPE_Coin:
		parser->CreateGameObject(new Coin(name, glm::vec3(x, y, -z), color), parser->GetObjectType(name));
		break;
		// DOOR
	case config::TYPE_Door:
		parser->CreateGameObject(new Door(name, glm::vec3(x, y, -z), color), parser->GetObjectType(name));
		break;
		// WALL
	case config::TYPE_Wall:
		parser->CreateGameObject(new Wall(name, glm::vec3(x, y, -z), color), parser->GetObjectType(name));
		break;
	default:
		break;
	}

	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      AddTextField()
//------------------------------------------------------------------------------------------------------------
void LuaParser::AddTextField(TextField* pTextField) {
	_textFields.push_back(pTextField);
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: createTextField(font name, font size)
//------------------------------------------------------------------------------------------------------------
int createTextField(lua_State * pLua) {
	TextField* textField = new TextField(lua_tostring(pLua, -2), lua_tointeger(pLua, -1));
	textField->getText()->setPosition(sf::Vector2f(300, 300));
	parser->AddTextField(textField);
	lua_pushlightuserdata(pLua, textField);
	std::cout << "LuaParser: TextField :Created" << std::endl;
	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setText(TextField, string)
//------------------------------------------------------------------------------------------------------------
int setText(lua_State * pLua) {
	TextField * textField = (TextField*)lua_touserdata(pLua, -2);
	textField->getText()->setString(lua_tostring(pLua, -1));
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      RenderTextFields()
//------------------------------------------------------------------------------------------------------------
void LuaParser::RenderTextFields() {
	for (vector<TextField*>::iterator itr = _textFields.begin();itr != _textFields.end(); itr++) {
		window->draw(*(*itr)->getText());
		std::cout << (std::string)(*itr)->getText()->getString() << " | " << (*itr)->getText()->getPosition().y << std::endl;
	}
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setMainCharacter(actor)
//------------------------------------------------------------------------------------------------------------
int setMainCharacter(lua_State * pLua) {
	if (!lua_islightuserdata(pLua, -1)) throw "expected: player";
	Player * player = (Player*)lua_touserdata(pLua, -1);
	player->setBehaviour(new KeysBehaviour()); // W S A D
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: moveBack(actor1, actor2)
//------------------------------------------------------------------------------------------------------------

int moveBack(lua_State * pLua) {
	GameObject * actor1 = (GameObject*)lua_touserdata(pLua, -2);
	GameObject * actor2 = (GameObject*)lua_touserdata(pLua, -1);
	// Good for sliding movement 0.01f
	glm::vec3 aPosition = actor1->getWorldPosition();
	glm::vec3 bPosition = actor2->getWorldPosition();
	glm::vec3 knockBack = (bPosition - aPosition)*0.1f;
	actor1->setTransform(glm::translate((-knockBack) + aPosition));
	std::cout << "MOVE BACK: " << glm::length(knockBack) << " units" << std::endl;

	return 0;
}

//------------------------------------------------------------------------------------------------------------
//                                                      Lua: destroy(actor)
//------------------------------------------------------------------------------------------------------------
int destroy(lua_State * pLua) {
	if (!lua_islightuserdata(pLua, -1)) throw "expected: object to destroy";
	GameObject * gameObject = (GameObject*)lua_touserdata(pLua, -1);
	std::cout << "LuaParser - Object to be deleted: " << gameObject->getName() << " Of type: " << gameObject->getObjectType() << std::endl;
	parser->getWorld()->remove(gameObject);
	delete gameObject;
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: addListener(actor1, actor2, "collisionFunctionName")
//------------------------------------------------------------------------------------------------------------
int addListener(lua_State * pLua) {
	if (lua_gettop(pLua) == 0) return 0;

	if (!lua_islightuserdata(pLua, -3)) throw "expected: an actor1";
	//if (!lua_islightuserdata(pLua, -2)) throw "expected: an actor2";
	if (!lua_isstring(pLua, -1)) throw "expected: a collision resolution function as string";
	GameObject * actor1 = (GameObject*)lua_touserdata(pLua, -3);
	GameObject * actor2 = (GameObject*)lua_touserdata(pLua, -2);
	//std::string objectName = lua_tostring(pLua, -2);
	std::string collisionFunction = lua_tostring(pLua, -1);

	int typeA = actor1->getObjectType();
	int typeB = actor2->getObjectType();
	
	actor1->setCollisionFunction(collisionFunction, typeB);
	actor2->setCollisionFunction(collisionFunction, typeA);
	if (actor1->getCollisionFunction(typeB) != "")
	 std::cout << "addListener: " << actor1->getName() << " - " << actor2->getName() << " - "
			   << actor1->getCollisionFunction(typeB) << " :Registered" << std::endl;
	return 0;
}

//------------------------------------------------------------------------------------------------------------
//                                                      Lua: getMainCamera()
//------------------------------------------------------------------------------------------------------------
int getMainCamera(lua_State * pLua) {
	Camera* camera = parser->getWorld()->getMainCamera();
	lua_pushlightuserdata(pLua, camera);
	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setPosition(actor, x, ,y, z)
//------------------------------------------------------------------------------------------------------------
int setPosition(lua_State * pLua) {
	GameObject * gameObject = (GameObject*)lua_touserdata(pLua, -4);
	float x = lua_tonumber(pLua, -3);
	float y = lua_tonumber(pLua, -2);
	float z = lua_tonumber(pLua, -1);
	gameObject->setLocalPosition(glm::vec3(x, y, -z));
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: getPosition(actor, "x/y/z")
//------------------------------------------------------------------------------------------------------------
int getPosition(lua_State * pLua) {
	GameObject * gameObject = (GameObject*)lua_touserdata(pLua, -2);
	std::string axis = lua_tostring(pLua, -1);
	if (axis == "x" || axis == "X") lua_pushnumber(pLua, gameObject->getWorldPosition().x);
	else if (axis == "y" || axis == "Y") lua_pushnumber(pLua, gameObject->getWorldPosition().y);
	else if (axis == "z" || axis == "Z") lua_pushnumber(pLua, gameObject->getWorldPosition().z);

	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setRotation(actor, x, y, z)
//------------------------------------------------------------------------------------------------------------
int setRotation(lua_State * pLua) {
	GameObject * gameObject = (GameObject*)lua_touserdata(pLua, -4);
	if (gameObject == NULL) return 0;
	float x = lua_tonumber(pLua, -3);
	float y = lua_tonumber(pLua, -2);
	float z = lua_tonumber(pLua, -1);
	glm::mat4 matrix = glm::translate(gameObject->getWorldPosition()) *
					   glm::rotate(glm::radians(-y), glm::vec3(0, 1, 0)) * glm::rotate(glm::radians(-x), glm::vec3(1, 0, 0)) * glm::rotate(glm::radians(-z), glm::vec3(0, 0, 1));
	gameObject->setTransform(matrix);
	std::cout << x << "|" << y << "|" << z << std::endl;
	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setScale(actor, x, y, z)
//------------------------------------------------------------------------------------------------------------
int setScale(lua_State * pLua) {
	GameObject * gameObject = (GameObject*)lua_touserdata(pLua, -4);
	if (gameObject == NULL) return 0;
	float x = lua_tonumber(pLua, -3);
	float y = lua_tonumber(pLua, -2);
	float z = lua_tonumber(pLua, -1);
	gameObject->scale(glm::vec3(x, y, z));
	std::cout << "LuaParser: " << gameObject->getName() << " :Scaled" << std::endl;
	return 0;
}

//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setFollowee(actor1, actor2)
//------------------------------------------------------------------------------------------------------------
int setFollowee(lua_State * pLua) {
	GameObject * follower = (GameObject*)lua_touserdata(pLua, -2);
	GameObject * followee = (GameObject*)lua_touserdata(pLua, -1);

	follower->setBehaviour(new CameraFollowBehaviour(followee));

	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: setOrbit(actor1, actor2)
//------------------------------------------------------------------------------------------------------------
int setOrbit(lua_State * pLua) {
	GameObject * orbiter = (GameObject*)lua_touserdata(pLua, -2);
	GameObject * target = (GameObject*)lua_touserdata(pLua, -1);

	orbiter->setBehaviour(new CameraOrbit(target, parser->window, 15, sf::Vector2f(-90, 0), 2));

	return 0;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: input(std::string)
//------------------------------------------------------------------------------------------------------------
int input(lua_State * pLua) {
	std::string key = lua_tostring(pLua, -1);

	if (key == "r" && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) lua_pushboolean(pLua, true);
	else lua_pushboolean(pLua, false);

	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Lua: getName(actor)
//------------------------------------------------------------------------------------------------------------
int getName(lua_State * pLua) {
	GameObject * actor = (GameObject*)lua_touserdata(pLua, -1);
	lua_pushstring(pLua, actor->getName().c_str());

	return 1;
}
int getTop(lua_State * pLua) {
	lua_pushinteger(pLua, lua_gettop(pLua));
	return 1;
}
//------------------------------------------------------------------------------------------------------------
//                                                      Setup()
//------------------------------------------------------------------------------------------------------------
void LuaParser::Setup()
{
	lua_pushcfunction(lua, registerObjectName);
	lua_setglobal(lua, "registerObjectName"); //"''

	lua_pushcfunction(lua, importObject);
	lua_setglobal(lua, "importObject"); //"''

	lua_pushcfunction(lua, createObject);
	lua_setglobal(lua, "createObject"); //"''

	lua_pushcfunction(lua, setMainCharacter);
	lua_setglobal(lua, "setMainCharacter"); //"''

	lua_pushcfunction(lua, addListener);
	lua_setglobal(lua, "addListener"); //"''

	lua_pushcfunction(lua, destroy);
	lua_setglobal(lua, "destroy"); //"''

	lua_pushcfunction(lua, getMainCamera);
	lua_setglobal(lua, "getMainCamera"); //"''

	lua_pushcfunction(lua, setPosition);
	lua_setglobal(lua, "setPosition"); //"''

	lua_pushcfunction(lua, getPosition);
	lua_setglobal(lua, "getPosition"); //"''

	lua_pushcfunction(lua, setRotation);
	lua_setglobal(lua, "setRotation"); //"''

	lua_pushcfunction(lua, setScale);
	lua_setglobal(lua, "setScale"); //"''

	lua_pushcfunction(lua, setFollowee);
	lua_setglobal(lua, "setFollowee"); //"''

	lua_pushcfunction(lua, setOrbit);
	lua_setglobal(lua, "setOrbit"); //"''

	lua_pushcfunction(lua, moveBack);
	lua_setglobal(lua, "moveBack"); //"''

	lua_pushcfunction(lua, input);
	lua_setglobal(lua, "input"); //"''

	lua_pushcfunction(lua, getName);
	lua_setglobal(lua, "getName"); //"''

	lua_pushcfunction(lua, getTop);
	lua_setglobal(lua, "getTop"); //"''

	lua_pushcfunction(lua, createTextField);
	lua_setglobal(lua, "createTextField"); //"''

	lua_pushcfunction(lua, setText);
	lua_setglobal(lua, "setText"); //"''

	lua_pushcfunction(lua, say);
	lua_setglobal(lua, "say");

	lua_pushcfunction(lua, visit);
	lua_setglobal(lua, "visit");

	currentFunction = "start"; //"'' set startpoint to main
}
//------------------------------------------------------------------------------------------------------------
//                                                      Load()
//------------------------------------------------------------------------------------------------------------
void LuaParser::Load() {

	currentFunction = "start";
	luaL_loadfile(lua, "mge/scripts/exported_scene.lua");//load file
	int result = lua_pcall(lua, 0, 0, 0);//run file
	if (result != LUA_OK) {//if there is an error
		if (lua_isstring(lua, -1)) {//show error
			std::cout << "Lua error: " << lua_tostring(lua, -1) << std::endl;
		}
		else {//if error is nil, give default message
			std::cout << "unknown lua error" << std::endl;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
//                                                      LuaParser()
//------------------------------------------------------------------------------------------------------------
LuaParser::LuaParser(sf::RenderWindow * pWindow, World * pWorld) {
	if (parser != NULL) throw "Instance of luaParser already exists";
	else {
		parser = this;
		imageCache = std::map<std::string, sf::Texture*>();
		window = pWindow;
		_world = pWorld;
		lua = luaL_newstate();
		luaL_openlibs(lua);

		Setup();
		Load();
		Step();
	}
}
