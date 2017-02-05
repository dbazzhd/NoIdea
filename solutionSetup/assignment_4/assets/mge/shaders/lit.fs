//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1
in vec2 fuv;
in vec4 worldNormal;
in vec4 worldVertex;
in mat4 fvMatrix;
// -------------------------
uniform vec3 diffuseColor;

uniform float quadraticAttenuation[2];
uniform float linearAttenuation[2];
uniform float lightIntensity[2];
uniform float fallAngle[2];
uniform float spotAngle[2];
uniform float lightType[2];
uniform vec3 lightColor[2];
uniform mat4 lightTransform[2];

uniform vec3 globalAmbient[2];
uniform float ambientIntensity[2];

uniform vec3 specularColor;
uniform float shininess;

out vec4 fragment_color;
// -------------------------
float fragmentEnlightment;
// -------------------------
void Directional(int pIndex);
void Point(int pIndex);
void Spot(int pIndex);
// -------------------------
vec4 Ambient(int pIndex);
vec4 Diffuse(int pIndex, vec4 pAmbientTerm);
vec4 Specular(int pIndex, vec4 pDiffuseTerm, vec3 pLightDirection);
vec4 Attenuate(int pIndex, vec4 pSpecularTerm, vec3 pDifferenceVector);
// -------------------------
void main( void ) {
    //fragmentEnlightment = 0.0;
    for (int i = 0; i < 2; i++) {
        if (lightType[i] == 1) Directional(i);
        if (lightType[i] == 2) Point(i);
        if (lightType[i] == 3) Spot(i);
    }

}

void Directional(int pIndex) {
	vec3 lightDirection = -vec3(lightTransform[pIndex][2]);
	fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(worldNormal))), 0);

    vec4 ambientTerm = Ambient(pIndex);
	if (fragmentEnlightment > 0.0) fragment_color += Specular(pIndex, Diffuse(pIndex, ambientTerm), lightDirection);
	else fragment_color += ambientTerm;
}

void Point(int pIndex) {
	vec3 lightDirection = vec3(worldVertex) - vec3(lightTransform[pIndex][3]);
	fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(worldNormal))), 0);
    
    vec4 ambientTerm = Ambient(pIndex);
	//do not attenuate ambientTerm

	if (fragmentEnlightment > 0.0) fragment_color += ambientTerm + Attenuate(pIndex, Specular(pIndex, Diffuse(pIndex, vec4(0,0,0,0)), lightDirection), lightDirection);
	else fragment_color += ambientTerm;
}

void Spot(int pIndex) {
	vec3 lightDirection = -vec3(lightTransform[pIndex][2]);
	float vlAngle = max(dot(-normalize(lightDirection), normalize(vec3(lightTransform[pIndex][3]) - vec3(worldVertex))), 0);
	fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(worldNormal))), 0);
	
	vec4 ambientTerm = Ambient(pIndex);
    vec4 spotLightContribution=Attenuate(pIndex, Specular(pIndex, Diffuse(pIndex, vec4(0,0,0,0)), lightDirection), vec3(worldVertex) - vec3(lightTransform[pIndex][3]));

	if (fragmentEnlightment > 0.0 && vlAngle > fallAngle[pIndex]) fragment_color += ambientTerm + spotLightContribution;
	else if (fragmentEnlightment > 0.0 && vlAngle > spotAngle[pIndex]) fragment_color += ambientTerm + vec4(vec3(spotLightContribution)*((vlAngle-spotAngle[pIndex])/(fallAngle[pIndex]-spotAngle[pIndex])),0);
	else fragment_color += ambientTerm;
}

// better: make vec3 out of this (and all other places):
vec4 Ambient(int pIndex) {
	return vec4(globalAmbient[pIndex] * diffuseColor,1);
}

vec4 Diffuse(int pIndex, vec4 pAmbientTerm) {
	return pAmbientTerm + vec4(lightColor[pIndex] * diffuseColor* fragmentEnlightment, 1);
}

vec4 Specular(int pIndex, vec4 pDiffuseTerm, vec3 pLightDirection) {
	return pDiffuseTerm + 
		vec4((specularColor * lightColor[pIndex] * pow(max(dot(reflect(normalize(pLightDirection), normalize(vec3(worldNormal))), normalize(vec3(fvMatrix[3]) - vec3(worldVertex))), 0), shininess)),1);
}

vec4 Attenuate(int pIndex, vec4 pSpecularTerm, vec3 pDifferenceVector) {
	float lightDistance = length(pDifferenceVector);
	return vec4(vec3(pSpecularTerm) / (lightIntensity[pIndex] +linearAttenuation[pIndex]*lightDistance+quadraticAttenuation[pIndex]*pow(lightDistance,2)), 1);
}