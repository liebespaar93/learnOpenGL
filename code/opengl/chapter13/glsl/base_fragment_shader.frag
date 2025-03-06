#version 400 core

#define PI 3.14159265359
#define PI_2 6.28318530718

uniform float u_time;
uniform vec2 u_resolution;

in vec4 ex_Color;
in vec4 ex_Position;
out vec4 out_Color;

float line(vec2 a, vec2 b, vec2 p, float width) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    vec2 hPoint = ba * h;

    float result = length(pa - hPoint);

    return result;
}

float crossProduct2D(vec2 u, vec2 v) {
    return u.x * v.y - u.y * v.x;
}

float dot2D(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float triangle(vec2 a, vec2 b, vec2 c, vec2 p) {
    vec2 v_pa = p - a;
    vec2 v_ba = b - a;
    vec2 v_ca = c - a;

    // 분모 계산
    float denom = crossProduct2D(v_ba, v_ca);

    // 행렬을 곱한 결과 (Barycentric 좌표 계산)
    float v = crossProduct2D(v_pa, v_ca) / denom;
    float w = crossProduct2D(v_ba, v_pa) / denom;
    float u = 1.0 - v - w;

    // 삼각형 내부 체크
    float inside = (u >= 0.0 && v >= 0.0 && w >= 0.0) ? 1.0 : 0.0;

    return inside;
}

float triangleBorder(vec2 a, vec2 b, vec2 c, vec2 p) {

    float ab = line(a, b, p, 0.01);
    float bc = line(b, c, p, 0.01);
    float ca = line(c, a, p, 0.01);

    return (min(min(ab, bc), ca));
}

void main() {
    vec3 color = vec3(0.0);
    vec2 st = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;

    vec2 p1 = vec2(-0.5, -0.5);
    vec2 p2 = vec2(0.5, -0.2);
    vec2 p3 = vec2(0.0, 0.3);

    float d = triangle(p1, p2, p3, st);

    float border = triangleBorder(p1, p2, p3, st);

    float borderWidth = 0.01;
    float borderOffset = 0.04;

    float borderline = step(borderOffset, border) * (1.0 - step(borderOffset + borderWidth, border));

    if(borderline > 0.0)
        color = vec3(0.3, 0.3, 0.7);
    if (d > 0.0)
        color = vec3(d);

    out_Color = vec4(color, 1.0);
}
