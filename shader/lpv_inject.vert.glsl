#version 330

uniform sampler2D Pos;

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec2 vtexcoord;

out vec2 vtc;
out vec2 ftexcoord;

vec4 unpack_pos(vec4 pos);
ivec2 coord3Dto2D(vec4 pos, int volume_divider);

void main(){
	ftexcoord = vtexcoord;

	vec4 pos = unpack_pos(texture(Pos, ftexcoord));
	ivec2 ipos = coord3Dto2D(pos, 64);
	vtc = vec2(ipos.x, ipos.y)/64.0;

	int size = 64;
	float hx = size;
	float hy = size*size;
	pos = vec4((ipos.x/hx-0.5)*2, (ipos.y/hy-0.5)*2, 0, 1.0);
	gl_Position = pos;
}

