#version 400 core

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform float u_time;
uniform int u_renderMode;
uniform int u_stepMode;

in vec4 ex_Color;
out vec4 out_Color;

void main() {
	vec2 st = gl_FragCoord.xy / u_resolution;
	float y = 0.0;
	vec3 color = vec3(0.0);

	if(u_renderMode == 2) {
		out_Color = ex_Color;
	} else if(u_renderMode == 3) {
		if(u_stepMode == 1) {
			y = st.x;
			color = vec3(y);
			out_Color = vec4(color, 1.0);
		} else if(u_stepMode == 2) {
			y = pow(st.x, 2.0);
			color = vec3(y);
			out_Color = vec4(color, 1.0);
		} else {
			out_Color = ex_Color;
		}
	} else {
		out_Color = ex_Color;
	}
}