#version 330 core
uniform mat4 uf_projection=mat4(1);
uniform mat4 uf_view=mat4(1);
uniform mat4 uf_model=mat4(1);


layout (location = 0)in vec4 vin_pos;
layout (location = 1)in int vin_color;
layout (location = 2)in int vin_ambient;


out vec3 fin_color;
out vec3 fin_surface_normal;
out vec2 fin_pos_in_tri;
out vec2 fin_size;

//PERMA CONSTS
const float ambients[4] = float[](1.0, 0.75,0.68,0.4);
const vec3 normals[6] = vec3[](vec3(0,1,0),vec3(0,-1,0),vec3(-1,0,0),vec3(1,0,0),vec3(0,0,1),vec3(0,0,-1));

//TEMP CONSTS
const vec3 tmp_light_dir = normalize(vec3(6,10,6));


vec3 getNormal(){
	return normals[((vin_ambient>>2) & 0x7)];
}
float getAmbient(){
	return ambients[vin_ambient&0x3];
}
int getWidth(){
	return ((vin_ambient>>5) & 0x1F) +1; 
}
int getHeight(){
	return ((vin_ambient>>10) & 0x1F) +1;
}
vec3 from16Bit(int c){
	vec3 r;
	r.r = ((c>>11)&0x1F)/32.0f;
	r.g = ((c>>5)&0x3F)/64.0f;
	r.b = (c&0x1F)/32.0f;
	return r;
}
void main(){
	vec4 world_position = uf_model*vin_pos;
	gl_Position = uf_projection*uf_view*world_position;
	fin_size = vec2(getWidth(),getHeight());
	switch (gl_VertexID%4){
		case 0:
			fin_pos_in_tri = vec2(0,0);
			break;
		case 1:
			fin_pos_in_tri = vec2(fin_size.x,0);
			break;
		case 2:
			fin_pos_in_tri = vec2(fin_size.x, fin_size.y);
			break;
		case 3:
			fin_pos_in_tri = vec2(0,fin_size.y);
			break;
	}
	
	fin_surface_normal = ( uf_model * vec4(getNormal(),0.0) ).xyz;
	float light_effectiveness = clamp(dot(fin_surface_normal,tmp_light_dir)*2f,0.7f,1f);
	vec3 color = from16Bit(vin_color);
		fin_color = light_effectiveness * (getAmbient()*from16Bit(vin_color)); 
	
}
