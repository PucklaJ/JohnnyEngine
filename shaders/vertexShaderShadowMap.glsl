#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

uniform mat4 lightSpaceMatrix;
uniform mat4 worldMatrix;

void main()
{	
	gl_Position = lightSpaceMatrix*worldMatrix*vec4(vertexPosition,1.0);
}