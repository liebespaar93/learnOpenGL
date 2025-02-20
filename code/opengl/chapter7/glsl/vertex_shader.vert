#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_Color;

uniform int u_renderMode;
uniform int u_stepMode;
uniform float u_time;

out vec4 ex_Color;

void main() {
    if(u_renderMode == 2) {
        if(u_stepMode == 1) {
            gl_Position = vec4(position.xxz, 1.0);
        } else if(u_stepMode == 2) {
            gl_Position = vec4(position.x, pow(position.y, 2.0), position.z, 1.0);
        } else
            gl_Position = vec4(position.xyz, 1.0);
    } else {
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
    ex_Color = in_Color;
}
