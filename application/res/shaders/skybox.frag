#version 300 es

precision mediump float;

in vec3 vTexCoords;

uniform samplerCube uSkybox;
uniform vec3 uFogColor;

const float lowerLimit = 0.0f;
const float upperLimit = 1.0f;

out vec4 fColor;

void main()
{
    vec4 skyboxFColor = texture(uSkybox, vTexCoords);

    float factor = (vTexCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);

    fColor = mix(vec4(uFogColor, 1.0), skyboxFColor, factor);
}