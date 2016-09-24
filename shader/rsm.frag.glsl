#version 330

uniform sampler2D Tex0;
uniform sampler2D ShadowMap;
uniform mat4 ShadowViewProj;
uniform int use_shadow = 0;

in vec4 fposition;
in vec2 ftexcoord;
in vec4 fnormal;

uniform vec3 CameraPos;
uniform vec3 Look;

uniform vec3 light_pos;
uniform vec3 light_dir;
uniform float light_intensity = 0.0;

layout (location = 0) out vec4 color0; //color
layout (location = 1) out vec4 normal; //normal
layout (location = 2) out vec4 pos; //position
layout (location = 3) out vec4 out_light; //light

vec4 pack(vec4 value, float size);
vec4 unpack(vec4 value, float size);

void main(){
	color0 = texture(Tex0, ftexcoord);

    vec3 light = normalize(fposition.xyz - light_pos);
    float l = max(dot(fnormal.xyz, -light) * light_intensity, 0.3);
    if(use_shadow == 1){
        vec4 shadow_screen_pos = ShadowViewProj * fposition;
        vec4 shadow_map_v = texture(ShadowMap, pack(shadow_screen_pos/shadow_screen_pos.w, 2.0).xy);
        float v0 = shadow_map_v.x;
        float v1 = (shadow_screen_pos.z)/shadow_screen_pos.w;
        if(v0 < v1){
            l = 0.3;
        }
    }

    out_light = color0 * l;
	normal = pack(fnormal, 2.0);
	pos = pack(fposition, 4096.0);
}
