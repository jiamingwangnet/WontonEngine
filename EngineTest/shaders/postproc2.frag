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

void main()
{
	//vec2 texCoords = won_PixelateCoords(won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)), won_DownscaleFactor );
	//vec2 ntexCoords = won_PixelateCoords(won_TexCoords, vec2(float(won_WindowWidth), float(won_WindowHeight)), won_DownscaleFactor + 0.3 );
	FragColor = texture(won_PostProcTexture, won_TexCoords) + won_NoiseBW(won_TexCoords * float(won_Time), -0.12, 0.0);
}