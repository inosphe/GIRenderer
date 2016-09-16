#version 330

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Pos;
uniform sampler2D LV_R;
uniform sampler2D LV_G;
uniform sampler2D LV_B;

in vec4 fposition;
in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;

void main(){
    int size = 64;
    vec4 pos = texture(Pos, ftexcoord);
    pos = pos * 32;
    ivec2 coord = ivec2(clamp(floor(pos.x), 0, size), clamp(floor(pos.y), 0, size) + size * clamp(floor(pos.z), 0, size));
    float r = texelFetch(LV_R, coord, 0).r;
    float g = texelFetch(LV_G, coord, 0).r;
    float b = texelFetch(LV_B, coord, 0).r;
	FragColor = vec4(r, g, b, 1.0);
	//FragColor = texture(LV_G, ftexcoord);
}