#version 330

in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D textureAddress;
uniform bool discardLowAlpha = true;

void main()
{
	fragColor = texture(textureAddress,textureCoords);
	if(discardLowAlpha && fragColor.w < 0.4)
		discard;
}