#version 120

uniform vec2 light_pos;
uniform sampler2D textures[8];

in vec3 vout_position;
in vec2 vout_uv;
in vec4 vout_color;
flat in int vout_tid;

out vec4 fout_color;

vec4 makeDepthColor(float rval){
	float rlin = (1 - rval) / 0.05;
	return vec4(rlin, rlin, rlin, 1);
}
void main() {
    if (vout_tid < 0) {
        fout_color = vout_color;
    }
    else {
        vec4 tcolor = texture(textures[0], vout_uv);
        fout_color = vec4(tcolor.x + vout_color.x, tcolor.y + vout_color.y,
                          tcolor.z + vout_color.z, tcolor.w * vout_color.w);
		//fout_color = makeDepthColor(tcolor.r);
      
    }
}