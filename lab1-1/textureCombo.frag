#version 150

in vec2 outTexCoord;
uniform sampler2D texUnit;
uniform sampler2D texUnit2;

out vec4 out_Color;

void main(void)
{

    //add the two textures
    vec3 tex_color1 = texture(texUnit, outTexCoord).rgb;
    vec3 tex_color2 = texture(texUnit2, outTexCoord).rgb;
    vec3 tex_color = mix(tex_color1, tex_color2, 0.5);
    // tex_color = tex_color1 + tex_color2;

    out_Color = vec4(tex_color, 1.0);


}