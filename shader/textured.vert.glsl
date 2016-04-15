#version 330

uniform mat4 ViewProjection;
uniform mat4 ObjectTransform;
uniform vec3 Look;

layout(location = 0) in vec4 vposition;
layout(location = 1) in vec2 vtexcoord;
layout(location = 2) in vec3 vnorm;

out vec4 fcolor;
out vec2 ftexcoord;

void main(){
    vec3 light = normalize(vec3(1.0, -1.0, 1.0));
    vec3 h = light + Look;
    h = normalize(h);
    float nh = dot(vnorm, h);

	fcolor = vec4(1.0) * max(dot(vnorm, light), 0.3) + pow(max(nh, 0), 10.0) *  vec4(1.0, 1.0, 1.0, 1.0);
	ftexcoord = vtexcoord;
	gl_Position = ViewProjection * ObjectTransform * vposition;
}

