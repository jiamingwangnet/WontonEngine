#version 330

out vec4 FragColor;
in vec2 won_TexCoords;

uniform sampler2D won_PostProcTexture;
uniform int won_WindowWidth;
uniform int won_WindowHeight;
uniform int won_Time;

#include <WON_POSTPROC_PIXELATE>
#include <WON_POSTPROC_NOISE>
//#include <WON_POSTPROC_COLOR_LIMITER>

void main()
{
	const float pfac = 1.4;
	vec2 pcoord = won_PixelateCoords(won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)), pfac );

	vec4 colorOut_0 = won_Pixelate(won_PostProcTexture, won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)),pfac);
	vec4 colorOut_1 = colorOut_0 + won_NoiseCL(pcoord * float(won_Time), -0.1, 0.1);
	//vec4 colorOut_2 = won_ColorLimiter(colorOut_1, 0.1);

	FragColor = colorOut_1;
}