#version 320 es

precision mediump float;
// Interpolated values from the vertex shaders
in vec3 fragmentColor;
out vec4 fragColor;

void main(){
	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
    fragColor = vec4(fragmentColor, 1);
}
