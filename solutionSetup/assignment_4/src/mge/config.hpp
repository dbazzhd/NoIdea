#ifndef config_hpp
#define config_hpp

namespace config {
#include <string>
	const std::string MGE_MODEL_PATH("mge/models/");
	const std::string MGE_TEXTURE_PATH("mge/textures/");
	const std::string MGE_SHADER_PATH("mge/shaders/");
	const std::string MGE_FONT_PATH("mge/fonts/");
	//const std::string MGE_LUA_PATH("mge/scripts/exported_scene.lua");

	const int TYPE_Player = 1;
	const int TYPE_Key = 2;
	const int TYPE_Coin = 3;
	const int TYPE_Door = 4;
	const int TYPE_Wall = 5;
}

#endif
