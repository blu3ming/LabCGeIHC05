#version 330
layout (location =0) in vec3 pos;
layout (location =1) in vec3 color;
out vec4 vColor;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
void main()
{
	gl_Position=projection * view * model * vec4(pos,1.0f);
	vColor=vec4(color,1.0f);
}