#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core\LuaParser.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/Light.hpp"
#include "mge/core/DirectionalLight.h"
#include "mge/core/PointLight.h"
#include "mge/core/SpotLight.h"

//#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.h"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "behaviours\CameraOrbit.h"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
	// camera - Camera //
	Camera* camera = new Camera("camera", glm::vec3(0, 10, 10));
	/*Y*/ //amera->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
	/*X*/ camera->rotate(glm::radians(-35.0f), glm::vec3(1, 0, 0));
	/*Z*/ //camera->rotate(glm::radians(0.0f), glm::vec3(0, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);


	//collisionResolver = new CollisionResolver(_world);
	//luaParser = new LuaParser(_window, _world);//, collisionResolver);

	//____________________________________________________________________________________________________________________________________________________________________________________________________________________
    
	_renderer->setClearColor(0,0,0);

	// MESHES
	//----------------------------------------------------------------------------
    // firstLightMesh - Mesh //
	Mesh* firstLightMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_smooth.obj");
	// LIGHTS
	//----------------------------------------------------------------------------
	// directionalLight - Directional Light //
	Light * directionalLight = new DirectionalLight("light",								// Name
											// -----------------------------------
												glm::vec3(0.0f, 1.25f, 0.0f),		// Position 
												glm::vec3(-90.0f, 0.0f, 0.0f),		// Rotation 
												glm::vec3(1,1,1),					// Scale
											// -----------------------------------
												glm::vec3(0.2f, 0.2f, 0.2f),		// AmbientColor 
												0.2f,								// AmbientIntensity
												glm::vec3(1.0f, 1.0f, 1.0f),		// LightColor
												1);									// LightIntensity
											// -----------------------------------
	directionalLight->setBehaviour(new KeysBehaviour());
	directionalLight->setMesh(firstLightMesh);
	directionalLight->setMaterial(new ColorMaterial(directionalLight->getLightColor()));
	//_world->add(directionalLight);
	// pointLight - Point Light //
	Light * pointLight = new PointLight("light",									// Name
											// -----------------------------------
												glm::vec3(0.0f, 0.5f, 0.0f),		// Position 
											// -----------------------------------
												glm::vec3(0.2f, 0.2f, 0.2f),		// AmbientColor 
												0.2f,								// AmbientIntensity
												glm::vec3(1.0f, 1.0f, 1.0f),		// LightColor
												1,									// LightIntensity
												1,									// LinearAttenuation
												0);									// QuadraticAttenuation
											// -----------------------------------
	pointLight->setBehaviour(new KeysBehaviour());
	pointLight->setMesh(firstLightMesh);
	pointLight->setMaterial(new ColorMaterial(pointLight->getLightColor()));
	_world->add(pointLight);
	// spotLight - Spot Light //
	Light * spotLight = new SpotLight("light",									// Name
										// -----------------------------------
											glm::vec3(0.0f, 10.0f, 0.0f),		// Position
											glm::vec3(-90.0f,0,0),				// Rotation
										// -----------------------------------
											glm::vec3(0.2f, 0.2f, 0.2f),		// AmbientColor 
											0.2f,								// AmbientIntensity
											glm::vec3(1.0f, 1.0f, 1.0f),		// LightColor
											1,									// LightIntensity
											45.0f,								// SpotAngle
											22.0f,								// FalloffAngle
											1,									// LinearAttenuation
											0);									// QuadraticAttenuation
										// -----------------------------------
	spotLight->setBehaviour(new KeysBehaviour());
	spotLight->setMesh(firstLightMesh);
	spotLight->setMaterial(new ColorMaterial(spotLight->getLightColor()));
	//_world->add(spotLight);

	// lights - vector//
	vector<Light*>* lights = new vector<Light*>();
	lights->push_back(pointLight);

	//____________________________________________________________________________________________________________________________________________________________________________________________________________________
	
	// plane - Ground //
	/*AbstractMaterial* planeTerrainMaterial = new TerrainMaterial(lights,
																 TerrainMaterial::loadFromName("diffuse1.jpg"),
																 TerrainMaterial::loadFromName("diffuse2.jpg"),
																 TerrainMaterial::loadFromName("diffuse3.jpg"),
																 TerrainMaterial::loadFromName("diffuse4.jpg"),
																 TerrainMaterial::loadFromName("myheightmap.png"),
																 TerrainMaterial::loadFromName("mysplatmap.png"));*/
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	AbstractMaterial*  planeMaterial = new LitMaterial(glm::vec3(0.7f, 0.5f, 0.7f), lights, glm::vec3(1.0f, 1.0f, 1.0f), 100);
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(32, 1, 32));
	plane->setMesh(planeMesh);
	plane->setMaterial(planeMaterial);
	_world->add(plane);

	// -----------------

	camera->setBehaviour(new CameraOrbit(plane, _window, 20, sf::Vector2f(-90.0f, 0.0f), 4.0f));
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
