#version 330 core

in float aValue;

out float vHeight;

uniform int uStartIndex;
uniform int uVertexCount;

void main() {
    vHeight = aValue * 2.0 - 1.0;
    int index = (gl_VertexID - uStartIndex + uVertexCount) % uVertexCount;
    float x = 2.0 / (uVertexCount - 1) * index - 1.0;
    gl_Position = vec4(x, vHeight, 0.0, 1.0);
}
