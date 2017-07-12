#version 120

attribute vec3 position;
attribute vec2 uv;
attribute float tid;
attribute vec4 color;


varying vec3 vout_position;
varying vec2 vout_uv;
varying float vout_tid;
varying vec4 vout_color;


void main(){
	vout_position = position;
	gl_Position = vec4(position.x, position.y, position.z,1.0);
	vout_uv = uv;
	vout_tid = tid;
	vout_color = color;
}