//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4	mMatrix;
uniform mat4	vMatrix;
uniform	mat4 	pMatrix;

out vec2 fuv;
out vec4 worldNormal;
out vec4 worldVertex;
out mat4 fvMatrix;

void main( void ) {

	gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertex,1);
	fuv = uv;
	worldNormal = mMatrix * vec4(normal, 0);
	worldVertex = mMatrix * vec4(vertex, 1);
	fvMatrix = inverse(vMatrix);
}