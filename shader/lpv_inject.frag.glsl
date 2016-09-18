#version 330

uniform sampler2D Light;
uniform sampler2D Pos;
uniform sampler2D LV_R;
uniform sampler2D LV_G;
uniform sampler2D LV_B;

in vec2 coord;
in vec2 ftexcoord;

layout(location = 0) out vec4 FragColor;

void main(){
    ivec2 ipos = ivec2(coord.x*64, coord.y*64);

	float r = texelFetch(LV_R, ipos, 0).r;
    float g = texelFetch(LV_G, ipos, 0).r;
    float b = texelFetch(LV_B, ipos, 0).r;
    FragColor = vec4(r, g, b, 1.0);
}