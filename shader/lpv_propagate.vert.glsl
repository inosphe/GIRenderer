#version 330

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec2 vtexcoord;

out vec3 coord;
out vec2 ftexcoord;
out vec4 fcolor;

void main(){
    ftexcoord = vtexcoord;
    coord = vposition;
	gl_Position = vec4(vposition, 1.0);
}

