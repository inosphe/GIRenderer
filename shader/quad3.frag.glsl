#version 330

uniform sampler2D Tex[3];

in vec2 ftexcoord;
in vec4 fcolor;

layout(location = 0) out vec4 FragColor[3];


void main(){
    for(int i=0; i<3; ++i){
	    FragColor[i] = texture(Tex[0], ftexcoord);
    }
}
