#version 150

in vec2 outTexCoord;
uniform sampler2D texUnit;
out vec4 out_Color;

float stepSize = 1f/512;


void main(void)
{

	//vec3 tex_color = vec3(texture(texUnit, vec2(outTexCoord.s , outTexCoord.t)).r, texture(texUnit, outTexCoord).g, texture(texUnit, outTexCoord).b);
	
	// From lab1-1.c we know the texture size, W 512, H 512 -> thus we have the stepsize
	//low pass filtering 

	// pixel 1
	vec3 tex_pix1 = vec3(texture(texUnit, outTexCoord - vec2(stepSize, stepSize)));
	// pixel 2
	vec3 tex_pix2 = vec3(texture(texUnit, outTexCoord - vec2(0, stepSize)));
	//...
 	vec3 tex_pix3 = vec3(texture(texUnit, outTexCoord + vec2(stepSize,stepSize)));
	vec3 tex_pix4 = vec3(texture(texUnit, outTexCoord - vec2(stepSize,0)));
	vec3 tex_pix5 = vec3(texture(texUnit, outTexCoord)); 	// center pixel
	vec3 tex_pix6 = vec3(texture(texUnit, outTexCoord + vec2(stepSize,0)));
	vec3 tex_pix7 = vec3(texture(texUnit, outTexCoord + vec2(-stepSize,stepSize)));
	vec3 tex_pix8 = vec3(texture(texUnit, outTexCoord + vec2(0,stepSize)));
	vec3 tex_pix9 = vec3(texture(texUnit, outTexCoord + vec2(stepSize,stepSize)));

	// summera

	vec3 tex_color = (tex_pix1 + tex_pix2 + tex_pix3 + tex_pix4+ tex_pix5 + tex_pix6 + tex_pix7 + tex_pix8 + tex_pix9)/9f;

    out_Color = vec4(tex_color, 1.0);
}
