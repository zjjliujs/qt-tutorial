#version 320 es

precision mediump float;
in vec3 f_color;
out vec4 fragColor;
void main()
{
  fragColor = vec4(f_color.x, f_color.y, f_color.z, 1.0);
}

