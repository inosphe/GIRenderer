#version 330

int size = 64;

ivec2 coord3Dto2D(vec4 pos, int volume_divider){
    pos = pos/volume_divider + size/2;
    ivec2 coord = ivec2(clamp(floor(pos.x), 0, size), clamp(floor(pos.y), 0, size) + size * clamp(floor(pos.z), 0, size));
    return coord;
}

ivec4 coord2Dto3D(ivec2 coord, int volume_divider){
    ivec4 pos = ivec4(coord.x, coord.y%size, int(coord.y/size), 1.0);
    pos = (pos-size/2);
    return pos;
}