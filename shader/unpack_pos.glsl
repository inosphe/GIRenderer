#version 330

vec4 unpack(vec4 pos, float size){
	vec4 _pos = (pos-0.5)*size;
	return _pos;
}

vec4 pack(vec4 value, float size){
    return value/size + 0.5;
}