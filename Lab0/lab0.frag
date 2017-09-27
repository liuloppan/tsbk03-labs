/*
 * random comment here
 * makes syntax highlight appaer
 * colors like springs sprouts
 */

#version 150

in float shade;

uniform float time;

out vec4 out_Color;

in vec2 frag_texcoord;

uniform sampler2D exampletexture;


void main(void)
{

	out_Color=vec4(shade * sin(time*2),shade,shade* sin(time),1.0);
	out_Color=texture(exampletexture,frag_texcoord);
	
}

