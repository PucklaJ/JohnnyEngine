#version 430 core

in vec2 textureCoords;
out vec4 fragColor;

#define DIRECT 0
#define BLENDING 1

uniform sampler2D textureAddress;
uniform int drawMode = 1;
uniform vec4 keyColor = {0.0,0.0,0.0,0.0};
uniform vec4 modColor = {1.0,1.0,1.0,1.0};

#define KEY_PADDING 0.1
#define ALPHA_DISCARD_PADDING 0.2

void main()
{
	fragColor = texture(textureAddress,textureCoords);
	if(drawMode != DIRECT && fragColor.a <= ALPHA_DISCARD_PADDING)
		discard;
    else if(keyColor.a != 0.0) // Color keying
    {
        if((keyColor.r <= fragColor.r+KEY_PADDING && keyColor.r >= fragColor.r-KEY_PADDING) &&
           (keyColor.g <= fragColor.g+KEY_PADDING && keyColor.g >= fragColor.g-KEY_PADDING) &&
           (keyColor.b <= fragColor.b+KEY_PADDING && keyColor.b >= fragColor.b-KEY_PADDING))
        {
            if(drawMode != DIRECT && keyColor.a >= 1.0-ALPHA_DISCARD_PADDING)
                discard;
            else
                fragColor.a -= keyColor.a;
        }
    }
    
    // Color Mod
    if(modColor.r != 1.0 || modColor.g != 1.0 || modColor.b != 1.0 || modColor.a != 1.0)
    {
        fragColor *= modColor;
        if(drawMode != DIRECT && fragColor.a < ALPHA_DISCARD_PADDING)
            discard;
    }
}