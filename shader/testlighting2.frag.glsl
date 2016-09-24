#version 330

uniform sampler2D Gradient[3];

in vec2 vtc;

layout(location = 0) out vec4 LPV_out[3];

void main(){
	for(int i=0; i<3; ++i)
	    LPV_out[i] = texelFetch(Gradient[i], ivec2(vtc.x, vtc.y), 0);
}