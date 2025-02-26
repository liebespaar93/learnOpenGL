#version 400 core

#define PI 3.14159265359
#define PI_2 6.28318530718

uniform float u_time;
uniform vec2 u_resolution;

in vec4 ex_Color;
in vec4 ex_Position;
out vec4 out_Color;

float CosWave(float x, float offset) {
    return (cos(x + offset) + 1.0) / 2.0;  // Normalize to [0, 1] range
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    float angle = atan(ex_Position.x, ex_Position.y) + (PI * -0.4);
    float radius = length(ex_Position.xy);

    float red = CosWave(angle, 0.0 * PI);
    float green = CosWave(angle, (2.0 * PI) / 3.0);
    float blue = CosWave(angle, (4.0 * PI) / 3.0);

    vec3 color = vec3(red, green, blue);

    color = mix(color, vec3(1.0), 1.0 - radius);
    out_Color = vec4(color, 1.0 < radius ? 0.0 : 1.0 );
}