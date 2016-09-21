#version 330

uniform sampler2D Light;
uniform sampler2D Pos;
uniform sampler2D Normal;
uniform sampler2D LPV[3];

uniform int lpv_size;
uniform int lpv_cellsize;

in vec2 ftexcoord;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );
vec4 SH_evaluate(vec3 dir);
ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize);
vec4 unpack(vec4 pos, float size);

layout(location = 0) out vec4 FragColor;

ivec3 directions[6] = ivec3[](
    ivec3(1, 0, 0)
    , ivec3(-1, 0, 0)
    , ivec3(0, 1, 0)
    , ivec3(0, -1, 0)
    , ivec3(0, 0, 1)
    , ivec3(0, 0, -1)
);

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

    vec4 pos = unpack(texture(Pos, ftexcoord), 4096.0);

    vec3 color = calcFinalColor(pos, normal);
    float t[6];
    t[0] = fract(pos.x/lpv_cellsize);
    t[1] = 1-fract(pos.x/lpv_cellsize);
    t[2] = fract(pos.y/lpv_cellsize);
    t[3] = 1-fract(pos.y/lpv_cellsize);
    t[4] = fract(pos.z/lpv_cellsize);
    t[5] = 1-fract(pos.z/lpv_cellsize);
    for(int i=0; i<6; ++i){
        color = color + calcFinalColor(pos+vec4(directions[i]*lpv_cellsize,0), normal) * t[i];
    }
    color /= 4.0;


    color[0] = max(color[0], 0);
    color[1] = max(color[1], 0);
    color[2] = max(color[2], 0);

    vec4 color4 = vec4(color, 0.0);

    //FragColor = color4*10;
    FragColor = texture(Light, ftexcoord) + color4;
}