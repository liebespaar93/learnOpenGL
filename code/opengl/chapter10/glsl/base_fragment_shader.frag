#version 400 core

#define PI 3.14159265359

uniform float u_time;
uniform vec2 u_resolution;

vec3 colorA = vec3(0.149, 0.141, 0.912);
vec3 colorB = vec3(1.000, 0.833, 0.224);

in vec4 ex_Color;
out vec4 out_Color;

void main() {
    vec2 st;
    vec3 color;
    float intensity;

    st = gl_FragCoord.xy / u_resolution.xy;
    
    intensity = abs(sin(u_time));
    color = mix(colorA, colorB, abs(sin(u_time + st.x)));

    out_Color = vec4(color, 1.0); // 그레이스케일 출력
}
