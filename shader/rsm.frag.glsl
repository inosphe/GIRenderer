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
layout (location = 3) out vec4 out_light; //light

void main(){
	color0 = texture(Tex0, ftexcoord);
	normal = fnormal;
	pos = fposition;
	vec4 _pos = (fposition - 1.0) * 4096.0 ;

    vec3 light = normalize(_pos.xyz - CameraPos);
	out_light = max(dot(fnormal.xyz, -light), 0.0) * color0;
}