#version 330

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Pos;
uniform sampler2D Gradient[3];

in vec3 coord;
in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;

vec4 unpack_pos(vec4 pos);
ivec2 coord3Dto2D(vec4 pos, int volume_divider);

void main(){
    vec4 pos = unpack_pos(texture(Pos, ftexcoord));
    ivec2 ipos = coord3Dto2D(pos, 64);

    float r = texelFetch(Gradient[0], ipos, 0).r;
    float g = texelFetch(Gradient[1], ipos, 0).r;
    float b = texelFetch(Gradient[2], ipos, 0).r;
	FragColor = vec4(r, g, b*2, 1.0);
	//FragColor = texture(LV_G, ftexcoord);
}