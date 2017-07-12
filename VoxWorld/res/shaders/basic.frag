#version 120

uniform vec2 light_pos;
uniform sampler2D textures[8];

varying vec3 vout_position;
varying vec2 vout_uv;
varying float vout_tid;
varying vec4 vout_color;

vec4 makeDepthColor(float rval){
	float rlin = (1 - rval) / 0.05;
	return vec4(rlin, rlin, rlin, 1);
}
void main() {
    if (vout_tid < 0 ) {
        gl_FragColor = vout_color;
    }
    else {
		//should be textures[vout_tid]
        vec4 tcolor = texture2D(textures[0], vout_uv);
        gl_FragColor = vec4(tcolor.x + vout_color.x, tcolor.y + vout_color.y,
                          tcolor.z + vout_color.z, tcolor.w * vout_color.w);
		//	gl_FragColor = vec4(1,0,0,1);
		//gl_FragColor = makeDepthColor(tcolor.r);
    }
}