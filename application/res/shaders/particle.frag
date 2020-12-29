#version 300 es

precision mediump float;

out vec4 o_Color;

uniform vec4 uColor;

void main()
{
	o_Color = uColor;
}