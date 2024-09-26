#version 330

out vec4 FragColor;
in vec2 won_TexCoords;

uniform sampler2D won_PostProcTexture;
uniform int won_WindowWidth;
uniform int won_WindowHeight;
uniform int won_Time;

#include <WON_POSTPROC_PIXELATE>
#include <WON_UTILITY_RANDOM>

const float pfac = 6.0;
const float contrast = 0.37;
const float brightness = 0.5;

const float c1 = 259.0/256.0;
const float c2 = 255.0/256.0;

float getPixelBW(vec4 color)
{
	float cl = ((color.r + color.g + color.b) / 3.0);
    float f = (c1 * (contrast + c2)) / (c2 * (c2 - contrast));
	return clamp(f * (cl - 0.5) + 0.5 + brightness, 0.0, 1.0);
}

void main()
{
	vec4 color0 = won_Pixelate(won_PostProcTexture, won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)), pfac);
	float cvalue = won_Random(won_TexCoords * float(won_Time)) <= getPixelBW(color0 * 0.5) ? 1.0 : 0.0;

	FragColor = vec4(vec3(cvalue), 1.0);
}