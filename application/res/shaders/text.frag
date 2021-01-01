#version 300 es

precision mediump float;

in vec2 vTexCoords;

uniform sampler2D text;
uniform vec3 uTextColor;

out vec4 fColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, vTexCoords).r);
    fColor = vec4(uTextColor, 1.0) * sampled;
}
