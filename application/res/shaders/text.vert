#version 300 es

precision mediump float;

layout (location = 0) in vec4 aVertexPosition;

out vec2 vTexCoords;

uniform mat4 uModelViewProjMatrix;

void main()
{
    gl_Position = uModelViewProjMatrix * vec4(aVertexPosition.xy, 0.0, 1.0);
    vTexCoords = aVertexPosition.zw;
}
