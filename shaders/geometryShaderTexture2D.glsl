#version 330

#define TRANS(vx,vy) ( ( vec2( transform*vec3( vx,vy,1.0 ) )/*+vec2( drawSize.x/2.0*scale.x,drawSize.y/2.0*scale.y)*/ ) / vec2( viewportSize.x/2.0,viewportSize.y/2.0 ))

layout(points) in;
layout(triangle_strip,max_vertices = 6) out;

out vec2 textureCoords;

uniform vec2 textureSize;
uniform mat3 transform;
uniform vec2 viewportSize;
//uniform vec2 scale;
uniform vec4 textureRegion;

#define TEXREG_X_L ( textureRegion.x / textureSize.x )
#define TEXREG_Y_D ( ( textureSize.y - textureRegion.y ) / textureSize.y )
#define TEXREG_Y_U ( TEXREG_Y_D - textureRegion.w / textureSize.y )
#define TEXREG_X_R ( TEXREG_X_L + textureRegion.z / textureSize.x )

void main()
{
	
	// LeftDown
	gl_Position = vec4( TRANS( -textureSize.x/2.0,-textureSize.y/2.0 ),-1,1 );
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_D);
	EmitVertex();

	// RightDown
	gl_Position = vec4(TRANS(textureSize.x/2.0,-textureSize.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_D);
	EmitVertex();

	// RightUp
	gl_Position = vec4(TRANS(textureSize.x/2.0,textureSize.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_U);
	EmitVertex();

	EndPrimitive();

	// RightUp
	gl_Position = vec4(TRANS(textureSize.x/2.0,textureSize.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_R,TEXREG_Y_U);
	EmitVertex();

	// LeftUp
	gl_Position = vec4(TRANS(-textureSize.x/2.0,textureSize.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_U);
	EmitVertex();

	// LeftDown
	gl_Position = vec4(TRANS(-textureSize.x/2.0,-textureSize.y/2.0),-1,1);
	textureCoords = vec2(TEXREG_X_L,TEXREG_Y_D);
	EmitVertex();

	EndPrimitive();
}