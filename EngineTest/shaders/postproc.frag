#version 330

out vec4 FragColor;
in vec2 won_TexCoords;

uniform sampler2D won_PostProcTexture;

layout(std140) uniform Won_StaticUniforms
{                          
	mat4 won_ProjectionMatrix;					
	mat4 won_ViewMatrix;      
	vec4 won_ViewPosition;	
	int won_Frames;				
	int won_Time;                  
	int won_WindowWidth;           
	int won_WindowHeight;
	float won_DownscaleFactor;
};

#include <WON_POSTPROC_PIXELATE>
#include <WON_POSTPROC_NOISE>
#include <WON_POSTPROC_DITHER>
#include <WON_POSTPROC_COLOR_LIMITER>

void main()
{
	const float pfac = 2.0;
	vec2 pcoord = won_PixelateCoords(won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)), pfac );
	vec2 fcoord = won_PixelateFragCoords(gl_FragCoord.xy, pfac );

	vec4 colorOut_0 = won_Pixelate(won_PostProcTexture, won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)),pfac);
	vec4 colorOut_1 = colorOut_0 + won_NoiseCL(pcoord * float(won_Time), -0.1, 0.1);
	vec4 colorOut_2 = won_BayerDither8x8(colorOut_1, fcoord, 2.5) - 0.05;
	vec4 colorOut_3 = won_ColorLimiterByParts(colorOut_2,5.0);

	FragColor = colorOut_3;
}