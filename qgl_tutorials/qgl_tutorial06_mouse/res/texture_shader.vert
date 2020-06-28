#version 320 es

in vec3 position;
in vec2 vertexUV;
out vec2 UV;
uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(position,1);
	UV = vertexUV;
}

