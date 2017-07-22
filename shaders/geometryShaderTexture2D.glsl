#version 330

#define TRANS(vx,vy) ( ( vec2( transform*vec3( vx,vy,1.0 ) )+vec2( width/2.0*scaleX,height/2.0*scaleY) ) / vec2( viewportWidth/2.0,viewportHeight/2.0 )/*+vec2( -1,-1 )*/ )

layout(points) in;
layout(triangle_strip,max_vertices = 6) out;

out vec2 textureCoords;

uniform float width;
uniform float height;
uniform mat3 transform;
uniform float viewportWidth;
uniform float viewportHeight;
uniform float scaleX;
uniform float scaleY;

void main()
{
	gl_Position = vec4(TRANS(-width/2.0,-height/2.0),-1,1);
	textureCoords = vec2(0.0,1.0);
	EmitVertex();

	gl_Position = vec4(TRANS(width/2.0,-height/2.0),-1,1);
	textureCoords = vec2(1.0,1.0);
	EmitVertex();

	gl_Position = vec4(TRANS(width/2.0,height/2.0),-1,1);
	textureCoords = vec2(1.0,0.0);
	EmitVertex();

	EndPrimitive();

	gl_Position = vec4(TRANS(width/2.0,height/2.0),-1,1);
	textureCoords = vec2(1.0,0.0);
	EmitVertex();

	gl_Position = vec4(TRANS(-width/2.0,height/2.0),-1,1);
	textureCoords = vec2(0.0,0.0);
	EmitVertex();

	gl_Position = vec4(TRANS(-width/2.0,-height/2.0),-1,1);
	textureCoords = vec2(0.0,1.0);
	EmitVertex();

	EndPrimitive();
}