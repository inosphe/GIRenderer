#version 330


layout(location = 0) in vec3 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec4 vcolor;

out vec3 coord;
out vec2 ftexcoord;
out vec4 fcolor;

void main(){
    coord = vposition;
	ftexcoord = vtexcoord;
	fcolor = vcolor;
	gl_Position = vec4(vposition, 1.0);
}

