#version 330

uniform sampler2D Light;
uniform sampler2D Diffuse;
uniform sampler2D Pos;
uniform sampler2D Normal;
uniform sampler2D LPV[3];

uniform int lpv_size;
uniform int lpv_cellsize;


uniform vec3 light_pos;
uniform vec3 light_dir;
uniform float light_intensity = 0.0;

in vec2 ftexcoord;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );
vec4 SH_evaluate(vec3 dir);
ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize);
vec4 pack(vec4 pos, float size);
vec4 unpack(vec4 pos, float size);

layout(location = 0) out vec4 FragColor;

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

void main(){
    vec3 normal = unpack(texture(Normal, ftexcoord), 2.0).xyz;
    normal = normalize(normal);

    vec4 pos = unpack(texture(Pos, ftexcoord), 4096.0);
    pos.w = 1.0;

    vec4 indirect_luminance = vec4(0.0);

    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<2; ++k){
                vec3 round_offset = vec3(dirs[i], dirs[j], dirs[k])*lpv_cellsize*0.5;
                vec4 rounded_pos = pos + vec4(round_offset, 0.0);
                vec3 c = calcFinalColor(rounded_pos, normal);

                vec4 center_pos = floor(rounded_pos/lpv_cellsize)*lpv_cellsize;
                center_pos += vec4(1, 1, 1, 0) * lpv_cellsize * 0.5;
                center_pos.w = 1.0;


                vec4 vt = pos - center_pos;
                vt = abs(vt);
                vt /= lpv_cellsize;

                float t = (1-vt.x)*(1-vt.y)*(1-vt.z);

                c = c*t;
                indirect_luminance += vec4(c, 0.0);
            }
        }
    }


    //color /= 8.0;
    //color /= 3.0;

    //vec3 light = normalize(pos.xyz - light_pos);
    //float direct_luminance = dot(normal.xyz, -light) * light_intensity;
    vec4 direct_luminance = texture(Light, ftexcoord);
    vec4 diffuse = texture(Diffuse, ftexcoord);

    //indirect_luminance = vec4(calcFinalColor(pos, normal), 0.0);
    //indirect_luminance *= 10;
    indirect_luminance = max(indirect_luminance, 0.0);

    vec4 color4 = diffuse * max(direct_luminance+indirect_luminance, 0.3);

    //vec4 color4 = vec4(color, 0.0);

    //FragColor = vec4(0.5);
    //FragColor = vec4(0);
    //FragColor += pack(color4, 2.0);
    FragColor += color4;

    FragColor = max(FragColor, 0.0);
}