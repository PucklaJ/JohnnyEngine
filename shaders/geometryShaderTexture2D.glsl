#version 450 core

#define TRANS(vx,vy) ( ( vec2( transform*vec3( vx,vy,1.0 ) )/*+vec2( drawSize.x/2.0*scale.x,drawSize.y/2.0*scale.y)*/ ) / vec2( viewportSize.x/2.0,viewportSize.y/2.0 ))

layout(points) in;
layout(triangle_strip,max_vertices = 6) out;

out vec2 textureCoords;

//uniform vec2 textureDimensions;
uniform mat3 transform;
uniform vec2 viewportSize;
//uniform vec2 scale;
uniform vec4 textureRegion;
uniform sampler2D textureAddress;

#define TEXREG_X_L ( textureRegion.x / textureDimensions.x )
#define TEXREG_Y_D ( ( textureDimensions.y - textureRegion.y ) / textureDimensions.y )
#define TEXREG_Y_U ( TEXREG_Y_D - textureRegion.w / textureDimensions.y )
#define TEXREG_X_R ( TEXREG_X_L + textureRegion.z / textureDimensions.x )

ivec2 textureDimensions;

void main()
{
	
    textureDimensions = textureSize(textureAddress,0);
    
	// LeftDown
	gl_Position = vec4( TRANS( -textureDimensions.x/2.0,-textureDimensions.y/2.0 ),-1,1 );
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_D);
	EmitVertex();

	// RightDown
	gl_Position = vec4(TRANS(textureDimensions.x/2.0,-textureDimensions.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_D);
	EmitVertex();

	// RightUp
	gl_Position = vec4(TRANS(textureDimensions.x/2.0,textureDimensions.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_U);
	EmitVertex();

	EndPrimitive();

	// RightUp
	gl_Position = vec4(TRANS(textureDimensions.x/2.0,textureDimensions.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_U);
	EmitVertex();

	// LeftUp
	gl_Position = vec4(TRANS(-textureDimensions.x/2.0,textureDimensions.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_U);
	EmitVertex();

	// LeftDown
	gl_Position = vec4(TRANS(-textureDimensions.x/2.0,-textureDimensions.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_D);
	EmitVertex();

	EndPrimitive();
}