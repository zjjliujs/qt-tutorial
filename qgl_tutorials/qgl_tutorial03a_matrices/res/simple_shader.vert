#version 320 es

// Input vertex data, different for all executions of this shader.
in vec3 position;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

// vertex color
out vec3   f_color;
in vec3    v_color;

void main()
{
  gl_Position =  MVP * vec4(position, 1);
  f_color = v_color;
}

