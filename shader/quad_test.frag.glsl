#version 330

in vec2 ftexcoord;
in vec4 fcolor;

layout(location = 0) out vec4 FragColor;


void main(){
	FragColor = fcolor;
}
