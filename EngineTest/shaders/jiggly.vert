#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;
layout (location = 3) in vec3 normal;

out vec2 texCoord;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 won_ModelViewProjMatrix;
uniform mat4 won_ModelMatrix;
uniform mat3 won_NormalMatrix;
uniform mat4 won_ModelViewMatrix;

vec3 pixelate(vec3 pos, float pfac)
{
	return floor(pos * pfac) / pfac;
}

void main()
{
	vec4 screenc = won_ModelViewProjMatrix * vec4(position.xyz, 1.0);
	gl_Position = vec4(pixelate(screenc.xyz/screenc.w, 45.0).xy * screenc.w, screenc.z, screenc.w);
	texCoord = uv;
	fragNormal = won_NormalMatrix * normal;
	fragPos = vec3(won_ModelMatrix * vec4(position, 1.0));
}