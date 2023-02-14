#version 330 core

attribute float aValue;

varying float vHeight;

uniform int uMeasuringCount;

void main() {
    float height = aValue * 2.0 - 1.0;
    vHeight = height;
    float x = 2.0 / uMeasuringCount * gl_VertexID - 1.0;
    gl_Position = vec4(x, height, 0.0, 1.0);
}
