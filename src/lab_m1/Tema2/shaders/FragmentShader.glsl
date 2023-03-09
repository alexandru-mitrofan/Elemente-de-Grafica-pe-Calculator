#version 330

// Input


// Uniforms for light properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// TODO(student): Declare any other uniforms

in vec3 v_color_out;
in vec3 v_normal_out;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    out_color = vec4(v_color_out, 1);

}