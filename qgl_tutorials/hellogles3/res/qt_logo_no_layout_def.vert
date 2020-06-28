#version 330

in vec4 vertex;
in vec3 normal;
out vec3 vert;
out vec3 vertNormal;
out vec3 color;
uniform mat4 projMatrix;
uniform mat4 camMatrix;
uniform mat4 worldMatrix;
uniform mat4 myMatrix;
uniform sampler2D sampler;
void main() {
   ivec2 pos = ivec2(gl_InstanceID % 32, gl_InstanceID / 32);
   vec2 t = vec2(float(-16 + pos.x) * 0.8, float(-18 + pos.y) * 0.6);
   float val = 2.0 * length(texelFetch(sampler, pos, 0).rgb);
   mat4 wm = myMatrix * mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, t.x, t.y, val, 1) * worldMatrix;
   color = texelFetch(sampler, pos, 0).rgb * vec3(0.4, 1.0, 0.0);
   vert = vec3(wm * vertex);
   vertNormal = mat3(transpose(inverse(wm))) * normal;
   gl_Position = projMatrix * camMatrix * wm * vertex;
}
