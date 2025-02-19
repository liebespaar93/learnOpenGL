#version 400 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_Color;
out vec4 ex_Color;
void main() {
    gl_Position = vec4(position.xyz, 1.0);   // Z 좌표 0으로, W 1로 설정
    ex_Color = in_Color;
}
