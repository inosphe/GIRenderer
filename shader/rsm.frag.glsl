#version 330

uniform sampler2D Tex0;

in vec4 fposition;
in vec2 ftexcoord;
in vec4 fnormal;

uniform vec3 CameraPos;
uniform vec3 Look;

uniform vec3 light_pos = vec3(30, 0, 0);
uniform vec3 light_dir = vec3(-0.5, -1, 0);
uniform float light_intensity = 0.0;

layout (location = 0) out vec4 color0; //color
layout (location = 1) out vec4 normal; //normal
layout (location = 2) out vec4 pos; //position
layout (location = 3) out vec4 out_light; //light

vec4 pack(vec4 value, float size);
vec4 unpack(vec4 value, float size);

void main(){
	color0 = texture(Tex0, ftexcoord);

	pos = pack(fposition, 4096.0);
	normal = pack(normalize(fnormal), 2.0);

    vec3 light = normalize(fposition.xyz - light_pos);
	out_light = max(dot(fnormal.xyz, -light), 0.3) * light_intensity * color0;

}