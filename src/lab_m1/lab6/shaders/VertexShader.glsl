#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;


// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = v_color;

    vec3 animated_position = v_position;
    animated_position.y += sin(Time + v_position.x * 2.0) * 0.3;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(animated_position, 1.0);

}
