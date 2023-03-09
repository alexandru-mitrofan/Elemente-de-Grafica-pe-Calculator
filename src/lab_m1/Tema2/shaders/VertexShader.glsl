#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 pozcar;
uniform float factors;


// Output values to fragment shader
out vec3 v_color_out;
out vec3 v_normal_out;
out vec2 v_texture_coord_out;
out vec3 v_position_out;



void main()
{
    v_color_out = v_color;
    vec4 newModel = Model * vec4(v_position,1) - vec4(0,factors * pow(length(vec3(Model * vec4(v_position,1))-pozcar),2),0,0);
    // TODO(student): Compute world space vertex position and normal,
    // and send them to the fragment shader
    gl_Position = Projection * View * newModel;

}