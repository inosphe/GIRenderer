#version 330

//Textures
uniform sampler2D Tex0;

//Shadow
uniform sampler2D ShadowMap;
uniform mat4 ShadowViewProj;
uniform int use_shadow = 0;

//Direct lighting
uniform vec3 CameraPos;
uniform vec3 Look;
uniform vec3 light_pos;
uniform vec3 light_dir;
uniform float light_intensity = 0.0;

//LPV
uniform sampler2D LPV[3];
uniform int lpv_size;
uniform int lpv_cellsize;

//utils
vec4 pack(vec4 value, float size);
vec4 unpack(vec4 value, float size);
vec4 SH_evaluateCosineLobe_direct( in vec3 dir );
vec4 SH_evaluate(vec3 dir);
ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize);

//Vertices input
in vec4 fposition;
in vec2 ftexcoord;
in vec4 fnormal;

layout(location = 0) out vec4 FragColor;

float evaluateLight(vec4 frag_pos, vec4 frag_normal, vec3 light_pos, vec3 light_dir, float light_intensity){
    float light_dist = abs(length((frag_pos.xyz - light_pos.xyz)));
    //vec3 light_dot = dot(frag_normal.xyz, -normalize(frag_pos.xyz - light_pos));
    float light_dot = dot(frag_normal.xyz, -light_dir.xyz);
    return max(light_dot * light_intensity / light_dist, 0.3);
}

float evaluateShadow(sampler2D depthMap, vec4 frag_pos, vec4 frag_normal, vec3 light_pos, mat4 matLightViewProj){
    vec4 frag_pos_lightspace = matLightViewProj * fposition;
    vec4 shadow_map_v = texture(depthMap, pack(frag_pos_lightspace/frag_pos_lightspace.w, 2.0).xy);
    float v0 = shadow_map_v.x;
    float v1 = (frag_pos_lightspace.z)/frag_pos_lightspace.w;

    if(v0 < v1){
        return 1.0;
    }
    else{
        return 0.0;
    }
}

vec3 axes[3] = vec3[](vec3(1,0,0), vec3(0,1,0), vec3(0, 0, 1));
float dirs[2] = float[](1, -1);

float calcFinalColorComponent(sampler2D lpv, ivec2 coord, vec3 dir){
    return dot(unpack(texelFetch(lpv, coord, 0), 8.0), SH_evaluate(dir));
}

vec3 calcFinalColor(vec4 pos, vec3 normal){
    ivec2 ipos = coord3Dto2D(pos, lpv_size, lpv_cellsize);
    float r = calcFinalColorComponent(LPV[0], ipos, -normal);
    float g = calcFinalColorComponent(LPV[1], ipos, -normal);
    float b = calcFinalColorComponent(LPV[2], ipos, -normal);
    return vec3(r, g, b);
}

vec4 evaluateLPV(vec4 frag_pos, vec3 normal){
    vec4 LPV_luminance = vec4(0.0);

    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<2; ++k){
                vec3 round_offset = vec3(dirs[i], dirs[j], dirs[k])*lpv_cellsize*0.5;
                vec4 rounded_pos = frag_pos + vec4(round_offset, 0.0);
                vec3 c = calcFinalColor(rounded_pos, normal);

                vec4 center_pos = floor(rounded_pos/lpv_cellsize)*lpv_cellsize;
                center_pos += vec4(1, 1, 1, 0) * lpv_cellsize * 0.5;
                center_pos.w = 1.0;

                vec4 vt = frag_pos - center_pos;
                vt = abs(vt);
                vt /= lpv_cellsize;

                float t = (1-vt.x)*(1-vt.y)*(1-vt.z);
                c = c*t;
                LPV_luminance += vec4(max(c, 0.0), 0.0);
            }
        }
    }

    return LPV_luminance;
}

void main(){
    vec4 diffuse = texture(Tex0, ftexcoord);

    float direct_luminance = evaluateLight(fposition, fnormal, light_pos, light_dir, light_intensity);
    float shadow = evaluateShadow(ShadowMap, fposition, fnormal, light_pos, ShadowViewProj);
    if(shadow>=1.0)
        direct_luminance = 0.3;

    vec4 indirect_luminance = evaluateLPV(fposition, fnormal.xyz);

    vec4 color = diffuse * max(direct_luminance+indirect_luminance, 0.3);
    color.a = 1.0;
    FragColor = color;
}