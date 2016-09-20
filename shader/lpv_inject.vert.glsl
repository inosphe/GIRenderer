#version 330

uniform sampler2D Pos;

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec4 color;

out vec2 vtc;
out vec2 ftexcoord;
out vec4 fcolor;

uniform int lpv_size;
uniform int lpv_cellsize;

vec4 unpack(vec4 pos, float size);
ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize);

void main(){
	float hx = lpv_size;
	float hy = lpv_size*lpv_size;

	ftexcoord = vtexcoord;

	vec4 pos = unpack(texture(Pos, ftexcoord), 4096.0);
	ivec2 ipos = coord3Dto2D(pos, lpv_size, lpv_cellsize);
	vtc = vec2(ipos.x/hx, ipos.y/hy);

	pos = vec4((ipos.x/hx-0.5)*2, (ipos.y/hy-0.5)*2, 0, 1.0);
	gl_Position = pos;

	fcolor = color;
}

