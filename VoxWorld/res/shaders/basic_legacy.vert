#version 120

in vec3 position;
in vec2 uv;
in int tid;
in vec4 color;


out vec3 vout_position;
out vec2 vout_uv;
out vec4 vout_color;
flat out int vout_tid;

void main(){
	vout_position = position;
	gl_Position = vec4(position.x, position.y, position.z,1.0);
	vout_uv = uv;
	vout_tid = tid;
	vout_color = color;
}