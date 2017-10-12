#version 150
// bump mapping should be calculated
// 1) in view coordinates
// 2) in texture coordinates

in vec2 outTexCoord;
in vec3 out_Normal;
in vec3 Ps;
in vec3 Pt;
in vec3 pixPos;  // Needed for specular reflections

uniform vec3 camPos;
uniform sampler2D texUnit;
out vec4 out_Color;

void main(void)
{

	// Calculate gradients here
	float offset = 1.0 / 256.0; // texture size, same in both directions

	float gradS = (texture(texUnit, outTexCoord+vec2(offset,0.0))-texture(texUnit, outTexCoord)).s * 10.0;
	float gradT = (texture(texUnit, outTexCoord+vec2(0.0, offset))-texture(texUnit, outTexCoord)).t * 10.0;

	vec2 gradient = vec2(gradS, gradT);

	//we want to use the bumpmap to affect the normal
    vec3 normal = normalize(out_Normal+vec3(gradient, 1.0));


	//------------light calculations-----------//
    vec3 light = vec3(0.0, 0.7, 0.7); // Light source in view coordinates

	// float diffuse, specular , shade;

	// // Diffuse
	// diffuse = dot(normal, light);
	// diffuse = max(0.0, diffuse); // No negative light
	
	// // Specular
	// vec3 r = reflect(-light, normalize(normal)); //	reverse, vec3 r = reflect(light, normalize(-normal));

	// vec3 v = normalize(camPos-pixPos); // View direction, reverse from here too
	// specular = dot(r, v);
	// if (specular > 0.0)
	// 	specular = 1.0 * pow(specular, 50.0);
	// specular = max(specular, 0.0);
	
	// shade = 0.7*diffuse + 3.0*specular;
	//---------------------------------------------//


	// Simplified lighting calculation.
	// A full solution would include material, ambient, specular, light sources, multiply by texture.
    out_Color = vec4( dot(normal, light)) ;//* texture(texUnit, outTexCoord);
    //out_Color = vec4(shade, shade, shade, 1.0 );
	    //out_Color = vec4(normal, 1.0 );

}
