#version 320 es

in vec3 a_Position;
in vec2 a_textureCoord;
out vec2 UV;
uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(a_Position,1);

    UV = a_textureCoord;
}

