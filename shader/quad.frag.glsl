#version 330

uniform sampler2D Tex0;

in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;


void main(){
	FragColor = texture(Tex0, ftexcoord);
}
