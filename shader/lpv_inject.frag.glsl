#version 330

uniform sampler2D Light;
uniform sampler2D Normal;
uniform sampler2D Pos;
uniform sampler2D LV_R;
uniform sampler2D LV_G;
uniform sampler2D LV_B;

in vec2 coord;
in vec2 ftexcoord;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );

layout(location = 0) out vec4 FragColor;

void main(){
    ivec2 ipos = ivec2(coord.x*64, coord.y*64);
    vec4 normal = texture(Normal, ftexcoord);
    vec4 SHcoeffs = SH_evaluateCosineLobe_direct( normal.xyz );

	FragColor = texture(Light, ftexcoord)*SHcoeffs;
}