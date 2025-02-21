#version 400 core

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform float u_time;
uniform int u_renderMode;
uniform int u_stepMode;

in vec4 ex_Color;
in vec4 ex_Position;
out vec4 out_Color;

void main() {
	vec2 st = gl_FragCoord.xy / u_resolution;
	float y = 0.0;
	vec3 color = vec3(0.0);

	out_Color = ex_Color;
}