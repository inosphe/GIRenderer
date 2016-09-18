#version 330

vec4 unpack_pos(vec4 pos){
	vec4 _pos = (pos-1.0)*4096.0;
	_pos.w = 1.0;
	return _pos;
}