#version 330

in vec2 vertexUVOut;

out vec4 fragColor;

uniform sampler2D frameBuffer;

const float offset = 1.0 / 300;
vec2 offsets[9];

void calculateOffsets()
{
	offsets = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );
}

vec3 normalProcessing()
{
	float kernel[9] = float[](
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 0.0  
	);

	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(frameBuffer, vertexUVOut.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

	return col;
}

vec3 edgeDetectionProcessing()
{
	float kernel[9] = float[](
    1.0, 1.0, 1.0,
    1.0, -8.0, 1.0,
    1.0, 1.0, 1.0  
	);

	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(frameBuffer, vertexUVOut.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

	return col;
}

vec3 blurProcessing()
{
	float kernel[9] = float[](
    1.0, 2.0, 1.0,
    2.0, 4.0, 2.0,
    1.0, 2.0, 1.0  
	);

	for(int i = 0;i<9;i++)
		kernel[i] /= 16.0;

	vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(frameBuffer, vertexUVOut.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

	return col;
}


void main()
{
	calculateOffsets();

	vec3 col = normalProcessing();

	//float value = texture(frameBuffer,vertexUVOut).r;
	//vec3 col = vec3(value,value,value);

	fragColor = vec4(col,1.0);
}