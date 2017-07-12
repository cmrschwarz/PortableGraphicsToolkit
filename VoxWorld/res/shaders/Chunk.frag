#version 330 core


in vec3 fin_color;
in vec3 fin_surface_normal;
in vec2 fin_pos_in_tri;
in vec2 fin_size;
out vec4 fout_color;

void main(){
	vec3 surface_normal = normalize(fin_surface_normal);
	fout_color =  vec4(fin_color.r,fin_color.g,fin_color.b,1);
	float bt = 0.01;
	if(
		mod(fin_pos_in_tri.x,1)<bt||
		mod(fin_pos_in_tri.x,1)>1-bt||
		mod(fin_pos_in_tri.y,1)<bt||
		mod(fin_pos_in_tri.y,1)>1-bt
	   )
	 {
		//fout_color = vec4(0,0,0,1);
	 }
}
