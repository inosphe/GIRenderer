#version 330

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Pos;
uniform sampler2D LV_R;
uniform sampler2D LV_G;
uniform sampler2D LV_B;

in vec3 coord;
in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;

vec4 unpack_pos(vec4 pos);
ivec2 coord3Dto2D(vec4 pos);

void main(){
    vec4 pos = unpack_pos(texture(Pos, ftexcoord));
    ivec2 ipos = coord3Dto2D(pos);

    float r = texelFetch(LV_R, ipos, 0).r;
    float g = texelFetch(LV_G, ipos, 0).r;
    float b = texelFetch(LV_B, ipos, 0).r;
	FragColor = vec4(r, g, b*2, 1.0);
	//FragColor = texture(LV_G, ftexcoord);
}