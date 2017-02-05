#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Light.hpp"

#include <vector>

/**
 * Simple single color material.
 * This material uses no lights.
 * This material demonstrates how to render a single color material, and how to cache all attributes, uniforms and pass in a single MVP matrix to the shader.
 */
class LitMaterial : public AbstractMaterial
{
    public:
		LitMaterial(glm::vec3 pColor, vector<Light*> *pLights, glm::vec3 pSpecularColor, float pShininess);
        virtual ~LitMaterial();

        virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);

    private:
		vector<Light *> *_lights;
        //all the static properties are shared between instances of ColorMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
		static GLint _uQuadraticAttenuation;
		static GLint _uLinearAttenuation;
		static GLint _uLightIntensity;
		static GLint _uFallAngle;
		static GLint _uSpotAngle;
		static GLint _uLightType;
		static GLint _uLightTransform;
        static GLint _uPMatrix;
		static GLint _uVMatrix;
		static GLint _uMMatrix;
        static GLint _uDiffuseColor;
		static GLint _uGlobalAmbient;
		static GLint _uAmbientIntensity;
		static GLint _uLightColor;
		static GLint _uSpecularColor;
		static GLint _uShininess;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        //this one is unique per instance of color material
		glm::vec3 _diffuseColor;
		glm::vec3 _specularColor;
		float _shininess;
};

#endif // COLORMATERIAL_H
