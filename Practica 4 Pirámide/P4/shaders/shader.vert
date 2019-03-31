#version 330
layout (location =0) in vec3 pos;
out vec4 vColor;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 color;
void main()
{
	gl_Position=projection * view * model * vec4(pos,1.0f);
	vColor=vec4(color,1.0f);
}