#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in vec3 color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float nume;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;
out vec3 f_normal;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = normal;
    f_normal = normal;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4 (position, 1);
}