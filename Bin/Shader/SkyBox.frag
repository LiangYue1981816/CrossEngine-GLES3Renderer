#version 310 es
precision mediump float;
#include "engine.inc"


uniform sampler2D texAlbedo;

layout (location = 0) in vec2 inTexcoord;
layout (location = 0) out vec4 outFragColor;


void main()
{
	outFragColor = texture(texAlbedo, inTexcoord);
}
