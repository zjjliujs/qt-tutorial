#version 320 es

precision mediump float;
in vec2 UV;
out vec4 fragColor;
uniform sampler2D myTextureSampler;

void main(){
    fragColor = texture( myTextureSampler, UV );
}
