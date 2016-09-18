#version 330

uniform sampler2D Tex0;

in vec4 fposition;
in vec2 ftexcoord;
in vec4 fnormal;

uniform vec3 CameraPos;
uniform vec3 Look;

layout (location = 0) out vec4 color0; //color
layout (location = 1) out vec4 normal; //normal
layout (location = 2) out vec4 pos; //position

void main(){
	color0 = texture(Tex0, ftexcoord);
	normal = fnormal;
	pos = fposition/4096.0 + 1.0;;
}