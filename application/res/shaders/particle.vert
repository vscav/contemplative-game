  
#version 300 es

precision mediump float;

layout(location = 0) in vec3 aPosition;

uniform mat4 uModelViewProjMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uNormalMatrix;

void main()
{
    gl_Position =  uModelViewProjMatrix * vec4(aPosition, 1);
}