#include <glm.hpp>

#include "TerrainMaterial.h"
#include "mge\core\ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"


ShaderProgram* TerrainMaterial::_shader = NULL;

Texture* TerrainMaterial::loadFromName(std::string pFileName) {
	return Texture::load(config::MGE_TEXTURE_PATH + pFileName);
}

TerrainMaterial::TerrainMaterial(vector<Light*>* pLights, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4, Texture* pHeightMap, Texture* pSplatMap) :  _heightMap(pHeightMap), _splatMap(pSplatMap)  { 
	//std::cout << _textures->size() << "Size" << std::endl;
	_lazyInitializeShader();
	_lights = pLights;
	_diffuseTexture1 = pDiffuseTexture1;
	_diffuseTexture2 = pDiffuseTexture2;
	_diffuseTexture3 = pDiffuseTexture3;
	_diffuseTexture4= pDiffuseTexture4;
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.fs");
		_shader->finalize();
	}
}

void TerrainMaterial::setDiffuseTexture1(Texture* pDiffuseTexture1) {
	_diffuseTexture1 = pDiffuseTexture1;
}
void TerrainMaterial::setDiffuseTexture2(Texture* pDiffuseTexture2) {
	_diffuseTexture2 = pDiffuseTexture2;
}
void TerrainMaterial::setDiffuseTexture3(Texture* pDiffuseTexture3) {
	_diffuseTexture3 = pDiffuseTexture3;
}
void TerrainMaterial::setDiffuseTexture4(Texture* pDiffuseTexture4) {
	_diffuseTexture4 = pDiffuseTexture4;
}

void TerrainMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (/*_textures->size() <= 0 */ !_diffuseTexture1 || !_diffuseTexture2 || !_diffuseTexture3 || !_diffuseTexture4) return;

	_shader->use();
	// --- 
	GLfloat quadraticAttenuation[] = { _lights->at(0)->getQuadraticAttenuation() };
	glUniform1fv(_shader->getUniformLocation("quadraticAttenuation"), 1, quadraticAttenuation);
	GLfloat linearAttenuation[] = { _lights->at(0)->getLinearAttenuation() };
	glUniform1fv(_shader->getUniformLocation("linearAttenuation"), 1, linearAttenuation);
	GLfloat lightIntensity[] = { _lights->at(0)->getLightIntensity() };
	glUniform1fv(_shader->getUniformLocation("lightIntensity"), 1, lightIntensity);
	GLfloat fallAngle[] = { glm::cos(glm::radians(_lights->at(0)->getFallAngle())) };
	glUniform1fv(_shader->getUniformLocation("fallAngle"), 1, fallAngle);
	GLfloat spotAngle[] = { glm::cos(glm::radians(_lights->at(0)->getSpotAngle())) };
	glUniform1fv(_shader->getUniformLocation("spotAngle"), 1, spotAngle);

	GLfloat lightType[] = { _lights->at(0)->getType() };
	glUniform1fv(_shader->getUniformLocation("lightType"), 1, lightType);

	//set the global ambient intensity
	GLfloat ambientIntensity[] = { _lights->at(0)->getAmbientIntensity() };
	glUniform1fv(_shader->getUniformLocation("ambientIntensity"), 1, ambientIntensity);
	//set the light color
	glUniform3fv(_shader->getUniformLocation("lightColor"), 1, glm::value_ptr(_lights->at(0)->getLightColor()));
	//set specular color
	//glUniform3fv(_uSpecularColor, 1, glm::value_ptr(_lights->at(0)->_specularColor));
	//set specular shininess
	//GLfloat shininess[] = { _shininess };
	//glUniform1fv(_uShininess, 1, shininess);
	// ---
	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture1->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse1"), 0);
	//setup texture slot 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture2->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse2"), 1);
	//setup texture slot 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture3->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse3"), 2);
	//setup texture slot 3
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture4->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse4"), 3);
	//setup texture slot 4
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
	glUniform1i(_shader->getUniformLocation("heightMap"), 4);
	//setup texture slot 5
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
	glUniform1i(_shader->getUniformLocation("splatMap"), 5);

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));


	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
		);
}