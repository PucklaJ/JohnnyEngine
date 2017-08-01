#version 330

layout(std140) uniform TestBlock
{
	mat4 matrix4[2];
	mat2 matrix2[2];
	vec3 pos1[3];
} testBlock;

void main()
{
	vec4 pos;
	
	pos = vec4(testBlock.matrix2[0]*testBlock.matrix2[1]*testBlock.pos1[gl_VertexID].xy,testBlock.pos1[gl_VertexID].z,1.0);

	pos = testBlock.matrix4[0] * testBlock.matrix4[1] * pos;

	gl_Position = pos;
}