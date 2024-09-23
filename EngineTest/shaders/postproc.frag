#version 330

out vec4 FragColor;
in vec2 won_TexCoords;

uniform sampler2D won_PostProcTexture;
uniform int won_WindowWidth;
uniform int won_WindowHeight;

#include <WON_POSTPROC_PIXELATE>
//#include <WON_POSTPROC_COLOR_LIMITER>

void main()
{
	vec4 colorOut_0 = won_Pixelate(won_PostProcTexture, won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)),1.4);;
	//vec4 colorOut_1 = won_ColorLimiter(colorOut_0, 0.09);

	FragColor = colorOut_0;
}