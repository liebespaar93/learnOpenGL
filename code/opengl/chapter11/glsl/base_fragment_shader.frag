#version 400 core

#define PI 3.14159265359

uniform float u_time;
uniform vec2 u_resolution;

in vec4 ex_Color;
in vec4 ex_Position;
out vec4 out_Color;

float CosWave(float x, float d) {
    float cosValue = cos(x * PI + d) + 1;
    float cosClamp = clamp(cosValue, 0.0, 1.0);
    return cosClamp * cosClamp;
}


void main() {
    vec2 st;
    vec4 color;
    float intensity;

    st = gl_FragCoord.xy / u_resolution.xy;
    intensity = (sin(u_time));

    color.r = CosWave(ex_Position.x, ((0.0 * PI) / 3.0) + PI);
    color.g = CosWave(ex_Position.x, ((4.0 * PI) / 3.0) + PI);
    color.b = CosWave(ex_Position.x, ((2.0 * PI) / 3.0) + PI);
    color.a = 1.0;

    out_Color = mix(color, vec4(0.0), ((1.0 - ex_Position.y) / 2.0));
}
