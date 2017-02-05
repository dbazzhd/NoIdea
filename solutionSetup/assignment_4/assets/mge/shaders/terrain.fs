//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform float quadraticAttenuation;
uniform float linearAttenuation;
uniform float lightIntensity;
uniform float fallAngle;
uniform float spotAngle;
uniform float lightType;
uniform vec3 lightColor;

uniform vec3 globalAmbient;
uniform float ambientIntensity;

// ---
uniform sampler2D textureDiffuse1;
uniform sampler2D textureDiffuse2;
uniform sampler2D textureDiffuse3;
uniform sampler2D textureDiffuse4;
uniform sampler2D heightMap;
uniform sampler2D splatMap;

in mat4 fmMatrix;
in mat4 fvMatrix;
in vec4 worldVertex;
in vec2 time;
in vec2 texCoord;

out vec4 fragment_color;
float fragmentEnlightment;

vec4 Ambient();
vec4 Diffuse(vec4 pAmbientTerm);
vec4 Specular(vec4 pDiffuseTerm, vec3 pLightDirection, vec3 pNormal);
vec4 Attenuate(vec4 pSpecularTerm, vec3 pDifferenceVector);

void Directional(vec3 pNormal) {
    vec3 lightDirection = vec3(fmMatrix * vec4(0, -0.707, 0.707, 1));
    //vec3 lightDirection = -vec3(lightTransform[2]);
    fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(pNormal))), 0);

    vec4 ambientTerm = Ambient();
    if (fragmentEnlightment > 0.0) fragment_color = Specular(Diffuse(ambientTerm), lightDirection, pNormal);
    else fragment_color = ambientTerm;
}

void Point(vec3 pNormal) {
	vec3 lightDirection = vec3(worldVertex) - vec3(fvMatrix[3]);
	fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(pNormal))), 0);
    
    vec4 ambientTerm = Ambient();
	//do not attenuate ambientTerm

	if (fragmentEnlightment > 0.0) fragment_color = ambientTerm + Attenuate(Specular(Diffuse(vec4(0,0,0,0)), lightDirection, pNormal), lightDirection);
	else fragment_color = ambientTerm;
}

void Spot(vec3 pNormal) {
	//vec3 lightDirection = -vec3(lightTransform[2]);
	vec3 lightDirection = vec3(fvMatrix[2]);
	float vlAngle = max(dot(-normalize(lightDirection), normalize(vec3(fvMatrix[3]) - vec3(worldVertex))), 0);
	fragmentEnlightment = max(dot(-normalize(lightDirection), normalize(vec3(pNormal))), 0);
	
	vec4 ambientTerm = Ambient();
    vec4 spotLightContribution=Attenuate(Specular(Diffuse(vec4(0,0,0,0)), lightDirection, pNormal), vec3(worldVertex) - vec3(fvMatrix[3]));

	if (fragmentEnlightment > 0.0 && vlAngle > fallAngle) fragment_color = ambientTerm + spotLightContribution;
	else if (fragmentEnlightment > 0.0 && vlAngle > spotAngle) fragment_color = ambientTerm + vec4(vec3(spotLightContribution)*((vlAngle-spotAngle)/(fallAngle-spotAngle)),0);
	else fragment_color = ambientTerm;
}

void main( void ) {
    float offset = 1.0f/512.0f;
    vec3 minX = vec3(texCoord.x - offset, texture(heightMap, texCoord - vec2(offset, 0)).r, texCoord.y);
    //normalize(minX);
    vec3 maxX = vec3(texCoord.x + offset, texture(heightMap, texCoord + vec2(offset, 0)).r, texCoord.y);
    //normalize(maxX);
    vec3 minY = vec3(texCoord.x, texture(heightMap, texCoord - vec2(0, offset)).r, texCoord.y - offset);
    //normalize(minY);
    vec3 maxY = vec3(texCoord.x, texture(heightMap, texCoord + vec2(0, offset)).r, texCoord.y + offset);
    //normalize(maxY);

    vec3 nNormal = cross(normalize(maxY - minY), normalize(maxX - minX));

    if (texture(splatMap, texCoord).r == texture(splatMap, texCoord).g && texture(splatMap, texCoord).b == texture(splatMap, texCoord).g) {
        fragment_color += texture(textureDiffuse2, texCoord) * texture(splatMap, texCoord).r; //sand
    }
    else {  
        fragment_color += texture(textureDiffuse1, texCoord) * texture(splatMap, texCoord).b; //grass
        fragment_color += texture(textureDiffuse3, texCoord) * texture(splatMap, texCoord).g; //rocks
        fragment_color += texture(textureDiffuse4, texCoord) * texture(splatMap, texCoord).r; //snow
    }
    if (lightType == 1) Directional(nNormal);
    if (lightType == 2) Point(nNormal);
    if (lightType == 3) Spot(nNormal);
	//fragment_color = texture(textureDiffuse1,texCoord) * texture(splatMap, texCoord).r; //snow
	//fragment_color += texture(textureDiffuse2, texCoord) * texture(splatMap, texCoord).g; //rocks
	//fragment_color += texture(textureDiffuse3, texCoord) * texture(splatMap, texCoord).b; //sand
	//fragment_color += texture(textureDiffuse4, texCoord) * texture(splatMap, texCoord).a; //grass
}

vec4 Ambient(void) {
    return vec4(globalAmbient* vec3(fragment_color),1);
}

vec4 Diffuse(vec4 pAmbientTerm) {
    return pAmbientTerm + vec4(lightColor * vec3(fragment_color) * fragmentEnlightment, 1);
}

vec4 Specular(vec4 pDiffuseTerm, vec3 pLightDirection, vec3 pNormal) {
    return pDiffuseTerm + 
        //specColor, lightColor
        vec4((vec3(1.0f, 1.0f, 1.0f) * lightColor * pow(max(dot(reflect(normalize(pLightDirection), normalize(vec3(pNormal))), normalize(vec3(fvMatrix[3]) - vec3(worldVertex))), 0), 200)),1);
}

//vec4 Attenuate(vec4 pSpecularTerm, vec3 pDifferenceVector) {
//    float lightDistance = length(pDifferenceVector);
//    return vec4(vec3(pSpecularTerm) / (lightIntensity+linearAttenuation*lightDistance+quadraticAttenuation*pow(lightDistance,2)), 1);
//}
