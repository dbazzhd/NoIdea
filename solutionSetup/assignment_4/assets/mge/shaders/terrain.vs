//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D heightMap;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out mat4 fmMatrix;
out mat4 fvMatrix;
out vec4 worldVertex;
out vec2 texCoord; //make sure the texture coord is interpolated

void main( void ){
	float offset = texture(heightMap, uv).r*10;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex + vec3(0,offset,0), 1);
	texCoord = uv;
	worldVertex = modelMatrix * vec4(vertex + vec3(0,offset,0), 1);
	fvMatrix = inverse(viewMatrix);
	fmMatrix = modelMatrix;
}
