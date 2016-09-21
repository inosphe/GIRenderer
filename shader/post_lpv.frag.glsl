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

float calcFinalColor(sampler2D lpv, ivec2 coord, vec3 dir){
    return dot(unpack(texelFetch(lpv, coord, 0), 8.0), SH_evaluate(dir));
}

void main(){
    vec4 color = texture(Light, ftexcoord);
    vec3 normal = unpack(texture(Normal, ftexcoord), 2.0).xyz;

    vec4 pos = unpack(texture(Pos, ftexcoord), 4096.0);
    ivec2 ipos = coord3Dto2D(pos, lpv_size, lpv_cellsize);

    float r = calcFinalColor(LPV[0], ipos, -normal);
    float g = calcFinalColor(LPV[1], ipos, -normal);
    float b = calcFinalColor(LPV[2], ipos, -normal);

    r = max(r, 0);
    g = max(g, 0);
    b = max(b, 0);

    FragColor = vec4(r, g, b, 1.0)*10;
    //FragColor = texture(Light, ftexcoord) + vec4(r, g, b, 1.0)*4;
}