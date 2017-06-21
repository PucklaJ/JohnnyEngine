#version 330

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

out vec2 vertexUVOut;

void main()
{	
	gl_Position = vec4(vertexPosition,1.0);
	gl_Position.z = -1.0;

	vertexUVOut = vec2(vertexUV.x,vertexUV.y);
}