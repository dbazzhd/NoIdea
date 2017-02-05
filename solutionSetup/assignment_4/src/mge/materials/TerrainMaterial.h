#ifndef TERRAINMATERIAL_hpp
#define TERRAINMATERIAL_hpp

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Light.hpp"

/**
* Simple single texture material, this is a sample which doesn't cache anything upfront and
* passes in separate matrices for the MVP calculation
*/
class TerrainMaterial : public AbstractMaterial
{
public:
	// Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4,
	TerrainMaterial(vector<Light*>* pLights, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4, Texture* pHeightMap, Texture* pSplatMap);
	virtual ~TerrainMaterial();

	static Texture* loadFromName(std::string pFileName);

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture1(Texture* pDiffuseTexture1);
	void setDiffuseTexture2(Texture* pDiffuseTexture2);
	void setDiffuseTexture3(Texture* pDiffuseTexture3);
	void setDiffuseTexture4(Texture* pDiffuseTexture4);
	//void setHeightMap(Texture* pHeightMap);
	//void setSplatMap(Texture* pSplatMap);

protected:
private:
	vector<Light *> *_lights;
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	Texture* _diffuseTexture1;
	Texture* _diffuseTexture2;
	Texture* _diffuseTexture3;
	Texture* _diffuseTexture4;
	Texture* _heightMap;
	Texture* _splatMap;

	TerrainMaterial(const TerrainMaterial&);
	TerrainMaterial& operator=(const TerrainMaterial&);

};


#endif