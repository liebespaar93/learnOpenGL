#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_Color;

uniform int u_renderMode;
uniform int u_stepMode;
uniform float u_time;

out vec4 ex_Color;
out vec4 ex_Position;

#define PI 3.141592653589793

void main() {
    float x;
    float y;
    float piSpace = PI * 0.1;

    x = (position.x * (1.0 - piSpace)) - piSpace;
    y = (cos(position.x * PI * 2 + u_time) * 0.5) + 0.5;

    ex_Position = vec4(x, y, 0.0, 1.0);

    ex_Color = in_Color;
    gl_Position = ex_Position;
}
