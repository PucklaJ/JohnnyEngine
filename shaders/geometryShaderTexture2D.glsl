#version 330

#define TRANS(vx,vy) (vec2(transform*vec3(vx,vy,1.0)) / vec2(viewportSize.x/2.0,viewportSize.y/2.0))

#define POS_LU 0
#define POS_LD 1
#define POS_RU 2
#define POS_RD 3

#define FLIP_NONE 0
#define FLIP_HORIZONTALLY 1
#define FLIP_VERTICALLY 2
#define FLIP_DIAGONALLY 3

#define TEXTURE_COORDS_PADDING 0.3
#define TEXTURE_COORDS_PADDING_VEC2 vec2(TEXTURE_COORDS_PADDING*2.0,TEXTURE_COORDS_PADDING*2.0)
#define TEXTURE_COORDS_PADDING_VEC1 vec2(TEXTURE_COORDS_PADDING,TEXTURE_COORDS_PADDING)

layout(points) in;
layout(triangle_strip,max_vertices = 6) out;

out vec2 textureCoords;

uniform mat3 transform;
uniform vec2 viewportSize;
uniform ivec4 textureRegion;
uniform sampler2D textureAddress;
uniform bool isFrameBuffer;
uniform float depth;
uniform int flip;

vec2 textureDimensions;

float TEXREG_X_L=0.0;
float TEXREG_Y_U=0.0;
float TEXREG_Y_D=0.0;
float TEXREG_X_R=0.0;

void setGlobals();
void setPosition(int which);
void setTextureCoords(int which);
void _setTextureCoords(int which);
void setVertex(int which);

void main()
{
    setGlobals();
    
    setVertex(POS_LD);
    setVertex(POS_RD);
    setVertex(POS_RU);
    
    EndPrimitive();
    
    setVertex(POS_RU);
    setVertex(POS_LU);
    setVertex(POS_LD);
    
    EndPrimitive();
}

void setGlobals()
{
    textureDimensions = textureSize(textureAddress,0);
    
    vec4 _textureRegion = textureRegion;
    //_textureRegion.xy += TEXTURE_COORDS_PADDING_VEC1;
    //_textureRegion.zw -= TEXTURE_COORDS_PADDING_VEC2;
    
    TEXREG_X_L = ( _textureRegion.x / textureDimensions.x );
    TEXREG_Y_U = (isFrameBuffer ? ((textureDimensions.y-_textureRegion.y) / textureDimensions.y ) : ( 1.0- ((textureDimensions.y-_textureRegion.y) / textureDimensions.y )));
    TEXREG_Y_D = (isFrameBuffer ? ( TEXREG_Y_U - _textureRegion.w / textureDimensions.y ) : ( 1.0-(1.0-TEXREG_Y_U - _textureRegion.w / textureDimensions.y) ));
    TEXREG_X_R = ( TEXREG_X_L + _textureRegion.z / textureDimensions.x );
    
    TEXREG_X_L += (1.0/(2.0*textureDimensions.x))*TEXTURE_COORDS_PADDING;
    TEXREG_X_R -= (1.0/(2.0*textureDimensions.x))*TEXTURE_COORDS_PADDING;
    TEXREG_Y_D -= (1.0/(2.0*textureDimensions.y))*TEXTURE_COORDS_PADDING;
    TEXREG_Y_U += (1.0/(2.0*textureDimensions.y))*TEXTURE_COORDS_PADDING;
}

void setPosition(int which)
{
    switch(which)
    {
        case POS_LU:
            gl_Position = vec4(TRANS(-textureDimensions.x/2.0,textureDimensions.y/2.0),depth,1);
            break;
        case POS_LD:
            gl_Position = vec4( TRANS( -textureDimensions.x/2.0,-textureDimensions.y/2.0 ),depth,1 );
            break;
        case POS_RU:
            gl_Position = vec4(TRANS(textureDimensions.x/2.0,textureDimensions.y/2.0),depth,1);
            break;
        case POS_RD:
            gl_Position = vec4(TRANS(textureDimensions.x/2.0,-textureDimensions.y/2.0),depth,1);
            break;
    }
}

void setTextureCoords(int which)
{
    if(flip != FLIP_NONE)
    {
        if(flip == FLIP_HORIZONTALLY)
        {
            if(which == POS_LU)
            {
                _setTextureCoords(POS_RU);
                return;
            }
            else if(which == POS_LD)
            {
                _setTextureCoords(POS_RD);
                return;
            }
            else if(which == POS_RU)
            {
                _setTextureCoords(POS_LU);
                return;
            }
            else if(which == POS_RD)
            {
                _setTextureCoords(POS_LD);
                return;
            }
        }
        else if(flip == FLIP_VERTICALLY)
        {
            if(which == POS_LU)
            {
                _setTextureCoords(POS_LD);
                return;
            }
            else if(which == POS_LD)
            {
                _setTextureCoords(POS_LU);
                return;
            }
            else if(which == POS_RU)
            {
                _setTextureCoords(POS_RD);
                return;
            }
            else if(which == POS_RD)
            {
                _setTextureCoords(POS_RU);
                return;
            }
        }
        else if(flip == FLIP_DIAGONALLY)
        {
            if(which == POS_LD)
            {
                _setTextureCoords(POS_RU);
                return;
            }
            else if(which == POS_RU)
            {
                _setTextureCoords(POS_LD);
                return;
            }
            else if(which == POS_LU)
            {
                _setTextureCoords(POS_RD);
                return;
            }
            else if(which == POS_RD)
            {
                _setTextureCoords(POS_LU);
                return;
            }
        }
    }
    
    _setTextureCoords(which);
}

void _setTextureCoords(int which)
{
    switch(which)
    {
        case POS_LU:
            textureCoords = vec2(TEXREG_X_L,TEXREG_Y_U);
            break;
        case POS_LD:
            textureCoords = vec2(TEXREG_X_L,TEXREG_Y_D);
            break;
        case POS_RU:
            textureCoords = vec2(TEXREG_X_R,TEXREG_Y_U);
            break;
        case POS_RD:
            textureCoords = vec2(TEXREG_X_R,TEXREG_Y_D);
            break;
    }
}

void setVertex(int which)
{
    setPosition(which);
    setTextureCoords(which);
    EmitVertex();
}