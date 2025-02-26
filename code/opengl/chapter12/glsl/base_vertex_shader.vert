#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_Color;

out vec4 ex_Color;
out vec4 ex_Position;

void main() {
    ex_Color = in_Color;
    ex_Position = position;
    gl_Position = position;
}
