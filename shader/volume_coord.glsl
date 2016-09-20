#version 330

ivec2 coord3Dto2D(vec4 pos, int lpv_size, int lpv_cellsize){
    pos = pos/lpv_cellsize + lpv_size/2;
    ivec2 coord = ivec2(clamp(floor(pos.x), 0, lpv_size), clamp(floor(pos.y), 0, lpv_size) + lpv_size * clamp(floor(pos.z), 0, lpv_size));
    return coord;
}

ivec4 coord2Dto3D(ivec2 coord, int lpv_size, int lpv_cellsize){
    ivec4 pos = ivec4(coord.x, coord.y%lpv_size, int(coord.y/lpv_size), 1.0);
    pos = (pos-lpv_size/2)*lpv_cellsize;
    return pos;
}