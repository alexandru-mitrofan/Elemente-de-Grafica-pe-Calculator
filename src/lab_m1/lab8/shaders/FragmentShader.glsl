#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int Spot;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // TODO(student): Compute world space vectors
    vec3 L = normalize( light_position - world_position );
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );

    // TODO(student): Define ambient light component
    float ambient_light = 0.25;

    // TODO(student): Compute diffuse light component
    float diffuse_light = 0;
    diffuse_light = material_kd * max(dot(world_normal, L), 0);

    // TODO(student): Compute specular light component
    float specular_light = 0;
     
    float factorAtenuare = 0;
    factorAtenuare = 1/(pow(distance(world_position, light_position), 2) + 1);

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Gouraud (1971) shading method. There is also the Phong (1975) shading
    // method, which we'll use in the future. Don't mix them up!
    if (diffuse_light > 0)
    {
    specular_light = material_ks * pow(max(dot(H, world_normal), 0), material_shininess);
    }

    // TODO(student): Compute light
    float cut_off = radians(30);
    float spot_light = dot(-L, light_direction);
    float spot_light_limit = cos(cut_off);

    float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
    float light_att_factor = pow(linear_att, 2);


    
    // TODO(student): Send color light output to fragment shader
    if(Spot == 1){
        if(spot_light > cos(cut_off)){
            vec3 color = object_color * vec3(0,1,0) * (ambient_light + factorAtenuare * light_att_factor * (specular_light + diffuse_light));
            out_color = vec4(color, 1);
        }
        else{
        out_color = vec4((object_color * ambient_light), 1);
        }
    }
    else{
        vec3 color = object_color * (ambient_light + factorAtenuare * (specular_light + diffuse_light));
        out_color = vec4(color, 1);
    }
    

}