#version 150

in vec2 outTexCoord;
uniform sampler2D texUnit;
out vec4 out_Color;



void main(void)
{

	vec3 tex_color = vec3(texture(texUnit, outTexCoord));
	
	if(tex_color.r < 1.0 && tex_color.g < 1.0 && tex_color.b < 1.0 )
		{ 
			tex_color = vec3(0.0,0.0,0.0); // set values that aren't shiny to 0
		}else
		{
			tex_color -= 1.0; // get the diff so you can add it later
		}

    out_Color = vec4(tex_color, 1.0);
}
