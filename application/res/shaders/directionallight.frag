#version 300 es

precision mediump float;

in vec3 vViewSpacePosition;
in vec3 vViewSpaceNormal;

out vec3 fColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    return uLightIntensity * (uKd * dot(normalize(uLightDir_vs), vViewSpaceNormal) + uKs * pow((dot((normalize(-vViewSpacePosition) + normalize(uLightDir_vs)) / 2.0, vViewSpaceNormal)), uShininess));
}

void main() {
    fColor = blinnPhong();
}