#version 330

out vec4 color;

void main()
{
	color = vec4(cos(gl_FragCoord.x),sin(gl_FragCoord.y),sin(gl_FragCoord.x),1.0);
}