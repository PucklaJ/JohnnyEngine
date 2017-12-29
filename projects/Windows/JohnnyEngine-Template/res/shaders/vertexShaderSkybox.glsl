#version 330

in vec3 position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;

void main(void){
	
	gl_Position = projectionMatrix * vec4(position, 1.0); 
	textureCoords = position;
	
}