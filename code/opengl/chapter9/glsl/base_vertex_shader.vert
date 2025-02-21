#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_Color;

uniform int u_renderMode;
uniform int u_stepMode;
uniform float u_time;

out vec4 ex_Color;
out vec4 ex_Position;

float sigmoid(float x) {
    return 1 / (exp(-x) + 1.0);
}

void main() {
    float x;
    float y;
    if(u_renderMode == 2) {
        if(u_stepMode == 1) {
            ex_Position = vec4(position.xxz, 1.0);
        } else if(u_stepMode == 2) {
            x = (position.x + 1.0) / 2;
            y =  pow(x, 5.0);
            ex_Position = vec4(position.x, y * 2.0 - 1.0, position.z, 1.0);
        } else if(u_stepMode == 3) {
            x = position.x;
            y = x > 0 ? 1 : -1;
            ex_Position = vec4(position.x, y, position.z, 1.0);
        } else if(u_stepMode == 4) {
            x = position.x * 6;
            y = (sigmoid(x) -0.5 ) * 2;
            ex_Position = vec4(position.x, y, position.z, 1.0);
        } else
            ex_Position = vec4(position.xyz, 1.0);
    } else {
        ex_Position = vec4(position.x, position.y, position.z, 1.0);
    }
    ex_Color = in_Color;
    gl_Position = ex_Position;
}
