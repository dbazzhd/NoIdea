#include <glm.hpp>

#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Light.hpp"

ShaderProgram* LitMaterial::_shader = NULL;
GLint LitMaterial::_uQuadraticAttenuation = 0;
GLint LitMaterial::_uLinearAttenuation = 0;
GLint LitMaterial::_uLightIntensity = 0;
GLint LitMaterial::_uFallAngle = 0;
GLint LitMaterial::_uSpotAngle = 0;
GLint LitMaterial::_uLightType = 0;
GLint LitMaterial::_uLightTransform = 0;
GLint LitMaterial::_uPMatrix = 0;
GLint LitMaterial::_uVMatrix = 0;
GLint LitMaterial::_uMMatrix = 0;
GLint LitMaterial::_uDiffuseColor = 0;
GLint LitMaterial::_uGlobalAmbient = 0;
GLint LitMaterial::_uAmbientIntensity = 0;
GLint LitMaterial::_uLightColor = 0;
GLint LitMaterial::_uSpecularColor = 0;
GLint LitMaterial::_uShininess = 0;


GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;
GLint LitMaterial::_aUV = 0;

LitMaterial::LitMaterial(glm::vec3 pDiffuseColor, vector<Light *> *pLights, glm::vec3 pSpecularColor = glm::vec3(0, 0, 0), float pShininess = 0) 
	: _diffuseColor(pDiffuseColor), _lights(pLights), _specularColor(pSpecularColor), _shininess(pShininess)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"lit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"lit.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
		_uQuadraticAttenuation = _shader->getUniformLocation("quadraticAttenuation");
		_uLinearAttenuation = _shader->getUniformLocation("linearAttenuation");
		_uLightIntensity = _shader->getUniformLocation("lightIntensity");
		_uFallAngle = _shader->getUniformLocation("fallAngle");
		_uSpotAngle = _shader->getUniformLocation("spotAngle");
		_uLightType = _shader->getUniformLocation("lightType");
		_uLightTransform = _shader->getUniformLocation("lightTransform");
		_uMMatrix = _shader->getUniformLocation("mMatrix");
		_uVMatrix = _shader->getUniformLocation("vMatrix");
        _uPMatrix= _shader->getUniformLocation("pMatrix");
        _uDiffuseColor = _shader->getUniformLocation("diffuseColor");
		_uGlobalAmbient = _shader->getUniformLocation("globalAmbient");
		_uAmbientIntensity = _shader->getUniformLocation("ambientIntensity");
		_uLightColor = _shader->getUniformLocation("lightColor");
		_uSpecularColor = _shader->getUniformLocation("specularColor");
		_uShininess = _shader->getUniformLocation("shininess");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

LitMaterial::~LitMaterial()
{
    //dtor
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void LitMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	for (vector<Light*>::iterator itr = _lights->begin(); itr != _lights->end();itr++) {
		_shader->use();
		GLfloat quadraticAttenuation[] = { (*itr)->getQuadraticAttenuation() };
		glUniform1fv(_uQuadraticAttenuation, 1, quadraticAttenuation);
		GLfloat linearAttenuation[] = { (*itr)->getLinearAttenuation() };
		glUniform1fv(_uLinearAttenuation, 1, linearAttenuation);
		GLfloat lightIntensity[] = { (*itr)->getLightIntensity() };
		glUniform1fv(_uLightIntensity, 1, lightIntensity);
		GLfloat fallAngle[] = { glm::cos(glm::radians((*itr)->getFallAngle())) };
		glUniform1fv(_uFallAngle, 1, fallAngle);
		GLfloat spotAngle[] = { glm::cos(glm::radians((*itr)->getSpotAngle())) };
		glUniform1fv(_uSpotAngle, 1, spotAngle);
		GLfloat lightType[] = { (*itr)->getType() };
		glUniform1fv(_uLightType, 1, lightType);
		glUniformMatrix4fv(_uLightTransform, 1, GL_FALSE, glm::value_ptr((*itr)->getWorldTransform()));
		glm::mat4 mMatrix = pModelMatrix;
		glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(mMatrix));
		glm::mat4 vMatrix = pViewMatrix;
		glUniformMatrix4fv(_uVMatrix, 1, GL_FALSE, glm::value_ptr(vMatrix));
		glm::mat4 pMatrix = pProjectionMatrix;
		glUniformMatrix4fv(_uPMatrix, 1, GL_FALSE, glm::value_ptr(pMatrix));

		//set the material color
		glUniform3fv(_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
		//set the global ambient
		glUniform3fv(_uGlobalAmbient, 1, glm::value_ptr((*itr)->getGlobalAmbient()));
		//set the global ambient intensity
		GLfloat ambientIntensity[] = { (*itr)->getAmbientIntensity() };
		glUniform1fv(_uAmbientIntensity, 1, ambientIntensity);
		//set the light color
		glUniform3fv(_uLightColor, 1, glm::value_ptr((*itr)->getLightColor()));
		//set specular color
		glUniform3fv(_uSpecularColor, 1, glm::value_ptr(_specularColor));
		//set specular shininess
		GLfloat shininess[] = { _shininess };
		glUniform1fv(_uShininess, 1, shininess);
	}

		//now inform mesh of where to stream its data
		pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
		//draw normals
		//pMesh->drawDebugInfo(pModelMatrix, pViewMatrix, pProjectionMatrix);
	


}
