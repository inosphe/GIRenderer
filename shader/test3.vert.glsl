#version 330

uniform mat4 ViewProjection;
uniform mat4 ObjectTransform;

layout(location = 0) in vec4 vposition;
layout(location = 1) in vec4 vcolor;
layout(location = 2) in vec3 vnorm;
out vec4 fcolor;

void main(){
	fcolor = vec4(1.0) * max(dot(vnorm, vec3(1.0, -1.0, 1.0)), 0.0);
	gl_Position = ViewProjection * ObjectTransform * vposition;
}

