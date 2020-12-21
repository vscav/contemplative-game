#version 300 es

precision mediump float;

layout(location = 0) in vec3 aVertexPosition;

out vec3 vTexCoords;

uniform mat4 uModelViewProjMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uNormalMatrix;

void main()
{
    vTexCoords = aVertexPosition;
    vec4 position = uModelViewProjMatrix * vec4(aVertexPosition, 1.0);
    gl_Position = position.xyww;
}  