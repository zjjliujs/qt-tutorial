#version 320 es

precision mediump float;
in vec2 UV;
uniform sampler2D myTextureSampler;
out vec4 fragColor;
void main(){
    fragColor = texture( myTextureSampler, UV);
}
