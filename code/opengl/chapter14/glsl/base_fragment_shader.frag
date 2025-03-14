#version 400 core

#define PI 3.14159265359
#define PI_2 6.28318530718

uniform float u_time;
uniform vec2 u_resolution;

in vec4 ex_Color;
in vec4 ex_Position;
out vec4 out_Color;

mat2 rotate2d(float _angle) {
    return mat2(cos(_angle), -sin(_angle), sin(_angle), cos(_angle));
}

float box(in vec2 _st, in vec2 _size) {
    _size = vec2(0.5) - _size * 0.5;

    vec2 uv = step(_size, _st);
    uv *= step(_size, vec2(1.0) - _st); // 교집합

    return uv.x * uv.y;
}

float cross(in vec2 _st, float _size) {
    return box(_st, vec2(_size, _size / 4.)) +
        box(_st, vec2(_size / 4., _size));
}

bool line(vec2 a, vec2 b, vec2 p, float width) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    vec2 hPoint = ba * h;

    float result = length(pa - hPoint);

    return result > width;
}

mat2 scale(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}


void main() {
    vec3 color = vec3(1.0);
    
    vec2 st = (gl_FragCoord.xy / u_resolution) * 1.0;


    st -= vec2(0.5);
    st = rotate2d( sin(u_time)*PI ) * st;
    st = scale( vec2(sin(u_time)+1.0) ) * st;
    st += vec2(0.5);

    color = vec3(cross(st, 0.5));
    out_Color = vec4(color, st);
}
