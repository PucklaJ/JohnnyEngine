#version 330

in vec2 vertex;
in vec4 color;

out vec4 fragColor;

void main()
{
	gl_Position = vec4(vertex,-1,1);
	fragColor = color;
}