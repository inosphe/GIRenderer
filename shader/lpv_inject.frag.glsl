#version 330

uniform sampler2D Light;
uniform sampler2D Normal;
uniform sampler2D Pos;

in vec2 vtc;
in vec2 ftexcoord;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );

layout(location = 0) out vec4 LPV_out[3];

void main(){
    ivec2 ipos = ivec2(vtc.x*64, vtc.y*64);
    vec4 normal = texture(Normal, ftexcoord);
    vec4 SHcoeffs = SH_evaluateCosineLobe_direct( normal.xyz );

    vec4 light = texture(Light, ftexcoord);

	LPV_out[0] = light.r * SHcoeffs;
	LPV_out[1] = light.g * SHcoeffs;
	LPV_out[2] = light.b * SHcoeffs;
}