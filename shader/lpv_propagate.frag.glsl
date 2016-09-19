#version 330

uniform sampler2D LPV[3];
uniform sampler2D Pos;
uniform sampler2D Gradient[3];

in vec3 coord;
in vec2 ftexcoord;

vec4 SH_evaluateCosineLobe_direct( in vec3 dir );
vec4 SH_evaluate(vec3 dir);
ivec2 coord3Dto2D(vec4 pos, int volume_divider);
ivec4 coord2Dto3D(ivec2 coord, int volume_divider);

layout(location = 0) out vec4 LPV_out[3];

ivec3 directions[6] = ivec3[](
    ivec3(1, 0, 0)
    , ivec3(-1, 0, 0)
    , ivec3(0, 1, 0)
    , ivec3(0, -1, 0)
    , ivec3(0, 0, 1)
    , ivec3(0, 0, -1)
);

vec4 calc_sh(sampler2D lpv, vec3 coord, vec3 dir){
    vec4 shcoeff = texelFetch(lpv, coord3Dto2D(vec4(coord, 1.0), 1), 0);
    vec4 dirSH = SH_evaluate(dir);
    vec4 dirCosineLobeSH = SH_evaluateCosineLobe_direct(dir);
    return dot( shcoeff, dirSH ) * dirCosineLobeSH;
}

vec4 calc_sh2(sampler2D lpv, vec3 cell_idx, vec3 dir){
    vec4 shcoeff = texelFetch(lpv, coord3Dto2D(vec4(cell_idx, 1.0), 1), 0);
    return shcoeff;
}

void main(){
    int size = 64;
    vec4 shcoeff_accum[3] = vec4[](vec4(0), vec4(0), vec4(0));

    ivec4 cell_idx = coord2Dto3D(ivec2((coord.x/2+0.5)*size, (coord.y/2+0.5)*size*size), 1);

    for(int i=0; i<6; ++i){
        ivec3 dir = directions[i];
        ivec3 neighbor_cell_idx = cell_idx.xyz+dir;

        for(int j=0; j<3; ++j){
            shcoeff_accum[j] += calc_sh(LPV[j], neighbor_cell_idx, dir);
        }
    }

    for(int i=0; i<3; ++i){
        LPV_out[i] = shcoeff_accum[i];
        //LPV_out[i] = texture(LPV[i], ftexcoord);
        //LPV_out[i] = cell_idx/float(size*size)+0.5;
        //LPV_out[i] = vec4(0.5);
    }

    /*
    ivec2 ipos = coord3Dto2D(cell_idx, 1);
    float r = texelFetch(Gradient[0], ipos, 0).r;
    float g = texelFetch(Gradient[1], ipos, 0).r;
    float b = texelFetch(Gradient[2], ipos, 0).r;
    LPV_out[0] = vec4(r, 0, 0, 1.0);
    LPV_out[1] = vec4(0, g, 0, 1.0);
    LPV_out[2] = vec4(0, 0, b, 1.0);
    */
}