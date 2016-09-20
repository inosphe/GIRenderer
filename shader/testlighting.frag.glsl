#version 330

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Pos;
uniform sampler2D Gradient[3];

uniform int lpv_size;
uniform int lpv_cellsize;

in vec3 coord;
in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;

vec4 unpack(vec4 pos, float size);
ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize);

void main(){
    vec4 pos = unpack(texture(Pos, ftexcoord), 4096.0);
    ivec2 ipos = coord3Dto2D(pos, lpv_size, lpv_cellsize);

    float r = texelFetch(Gradient[0], ipos, 0).r;
    float g = texelFetch(Gradient[1], ipos, 0).r;
    float b = texelFetch(Gradient[2], ipos, 0).r;
	FragColor = vec4(r, g, b*2, 1.0);
	//FragColor = texture(Gradient[0], ftexcoord);
}