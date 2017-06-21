#version 330

layout(points) in;
layout(triangle_strip,max_vertices = 6) out;

out vec2 textureCoords;

uniform float width;
uniform float height;
uniform vec2 offset;

void main()
{
	gl_Position = vec4(offset,-1,1);
	textureCoords = vec2(0.0,1.0);
	EmitVertex();

	gl_Position = vec4(offset,-1,1) + vec4(width,0,0,0);
	textureCoords = vec2(1.0,1.0);
	EmitVertex();

	gl_Position = vec4(offset,-1,1) + vec4(width,height,0,0);
	textureCoords = vec2(1.0,0.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4(offset,-1,1) + vec4(width,height,0,0);
	textureCoords = vec2(1.0,0.0);
	EmitVertex();

	gl_Position = vec4(offset,-1,1) + vec4(0,height,0,0);
	textureCoords = vec2(0.0,0.0);
	EmitVertex();

	gl_Position = vec4(offset,-1,1);
	textureCoords = vec2(0.0,1.0);
	EmitVertex();

	EndPrimitive();
}