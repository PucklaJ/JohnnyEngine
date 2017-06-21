#version 330

in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D textureAddress;

void main()
{
	fragColor = texture(textureAddress,textureCoords);
	if(fragColor.w < 0.4)
		discard;
}