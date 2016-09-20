#version 330

uniform sampler2D Tex_src[3];
uniform sampler2D Tex_dst[3];

in vec2 ftexcoord;

vec4 pack(vec4 value, float size);
vec4 unpack(vec4 value, float size);

layout(location = 0) out vec4 FragColor[3];

void main(){
    for(int i=0; i<3; ++i){
        vec4 c = unpack(texture(Tex_dst[i], ftexcoord), 2.0) + unpack(texture(Tex_src[i], ftexcoord), 8.0);

        FragColor[i] = pack(c, 8.0);
    }
}
