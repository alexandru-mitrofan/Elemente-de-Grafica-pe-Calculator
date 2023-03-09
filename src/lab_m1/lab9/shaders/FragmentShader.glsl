#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int mixed;
// TODO(student): Declare various other uniforms

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    if (mixed==0){
        vec4 color = texture(texture_1, texcoord);
        float alpha = color.a;
        if(alpha < 0.5f) {
            discard;
        }
        out_color = color;}
    else{
        out_color = vec4(vec3(mix(texture2D(texture_1,texcoord),texture2D(texture_2,texcoord),0.5f)),1);

    }

}