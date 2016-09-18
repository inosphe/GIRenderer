#version 330

uniform mat4 ViewProjection;
uniform mat4 ObjectTransform;

layout(location = 0) in vec4 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec3 vnorm;

out vec4 fposition;
out vec2 ftexcoord;
out vec4 fnormal;

void main(){
	ftexcoord = vtexcoord;
	fposition = ObjectTransform * vposition;
    gl_Position = ViewProjection * fposition;
    fposition = fposition;
	fnormal = vec4(vnorm.xyz, 0.0);
}
