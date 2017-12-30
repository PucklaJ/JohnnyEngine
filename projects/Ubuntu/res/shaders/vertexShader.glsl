#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

out vec3 vertexPositionOut;
out vec3 vertexNormalOut;
out vec2 vertexUVOut;

uniform mat4 transform;
uniform mat4 worldMatrix;

void main()
{	
	gl_Position = transform*vec4(vertexPosition,1.0);

	vertexPositionOut = vec3(worldMatrix * vec4(vertexPosition,1.0));
	vertexNormalOut = normalize(vec3(worldMatrix * vec4(vertexNormal,0.0)));
	vertexUVOut = vec2(vertexUV.x,vertexUV.y);
}