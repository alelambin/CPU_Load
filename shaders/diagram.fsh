#version 330 core

in float vHeight;

vec3 color(float height) {
    float red = height > 0.0 ? 1.0 : height + 1.0;
    float green = height < 0.0 ? 1.0 : 1.0 - height;
    float blue = 0.0;
    return vec3(red, green, blue);
}

void main() {
    gl_FragColor = vec4(color(vHeight), 1.0);
}
