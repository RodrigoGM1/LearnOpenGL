#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D frontTexture;

void main(){
	FragColor = vec4(1.0, 0.0, 0.0, 0.0);
}