#version 400 core

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform float u_time;
in vec4 ex_Color;
out vec4 out_Color;

void main() {
	out_Color = ex_Color;
}