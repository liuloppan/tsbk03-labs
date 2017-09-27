#version 150

//in vec3 in_Color;
in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
uniform mat4 matrix;

uniform mat4 boneMat1;
uniform mat4 boneMat2;

uniform vec3 bonePos1;
uniform vec3 bonePos2;

out vec4 g_color;
const vec3 lightDir = normalize(vec3(0.3, 0.5, 1.0));

// Uppgift 3: Soft-skinning p� GPU
//
// Flytta �ver din implementation av soft skinning fr�n CPU-sidan
// till vertexshadern. Mer info finns p� hemsidan.

void main(void)
{
	// transformera resultatet med ModelView- och Projection-matriserna

	//original
	
	
	gl_Position = matrix * vec4(in_Position, 1.0);

	// s�tt r�d+gr�n f�rgkanal till vertex Weights
	vec4 color = vec4(in_TexCoord.x, in_TexCoord.y, 0.0, 1.0);

	// L�gg p� en enkel ljuss�ttning p� vertexarna 	
	float intensity = dot(in_Normal, lightDir);
	color.xyz *= intensity;

	g_color = color;
	
	
	/*
	// UPPGIFT 3
	gl_Position = vec4(in_Position, 1.0);

	// s�tt r�d+gr�n f�rgkanal till vertex Weights
	vec4 color = vec4(in_TexCoord.x, in_TexCoord.y, 0.0, 1.0);

	//invert position
	vec4 subPos1 = gl_Position - vec4(bonePos1, 1.0);
	vec4 subPos2 = gl_Position - vec4(bonePos2, 1.0);
	//transform rotation and move position back
	vec4 boneTotMat1 = vec4(bonePos1, 1.0) + subPos1 * boneMat1;
	vec4 boneTotMat2 = vec4(bonePos2, 1.0) + subPos2 * boneMat2;

	vec4 bonesMat = color.x * boneTotMat1 + color.y *boneTotMat2;

	//update gl_position
	gl_Position = matrix * bonesMat;


	// L�gg p� en enkel ljuss�ttning p� vertexarna 	
	float intensity = dot(in_Normal, lightDir);
	color.xyz *= intensity;

	g_color = color;
	*/
}

