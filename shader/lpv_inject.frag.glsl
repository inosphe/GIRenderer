#version 330

uniform sampler2D Light;
uniform sampler2D Normal;
uniform sampler2D Pos;

uniform int lpv_size;

in vec2 ftexcoord;
in vec4 fcolor;
in vec2 vtc;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );
vec4 pack(vec4 pos, float size);
vec4 unpack(vec4 pos, float size);

layout(location = 0) out vec4 LPV_out[3];

void main(){
    vec4 normal = unpack(texture(Normal, ftexcoord), 2.0);
    vec4 SHcoeffs = SH_evaluateCosineLobe_direct( normal.xyz );

    vec4 light = texture(Light, ftexcoord);

	LPV_out[0] = pack(light.x * SHcoeffs, 8.0);
	LPV_out[1] = pack(light.y * SHcoeffs, 8.0);
	LPV_out[2] = pack(light.z * SHcoeffs, 8.0);

	//for(int i=0; i<3; ++i)
	    //LPV_out[i] = vec4(1.0);
	    //LPV_out[i] = fcolor;
}