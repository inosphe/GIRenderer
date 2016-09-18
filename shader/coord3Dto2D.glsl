#version 330

ivec2 coord3Dto2D(vec4 pos){
    int volume_divider = 64;
    int size = 64;
    pos = pos/volume_divider + size/2;
    ivec2 coord = ivec2(clamp(floor(pos.x), 0, size), clamp(floor(pos.y), 0, size) + size * clamp(floor(pos.z), 0, size));
    return coord;
}