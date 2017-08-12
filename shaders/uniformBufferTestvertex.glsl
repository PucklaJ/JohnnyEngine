#version 330

layout(std140) uniform TestBlock
{
	vec2 pos[3];
	vec3 color[3];
} testBlock;

out vec3 vertexColor;

void main()
{
	gl_Position = vec4(testBlock.pos[gl_VertexID],0.0,1.0);
	vertexColor = testBlock.color[gl_VertexID];
}


