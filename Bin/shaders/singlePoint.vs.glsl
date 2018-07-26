#version 420 core

layout (location = 0) in vec4 ptPos;
layout (location = 1) in vec4 ptColor;

out VS_OUT
{
    vec4 ptPos;
    vec4 ptColor;
} vs_out;

void main(void)
{
    vs_out.ptPos = ptPos;
    gl_Position= vs_out.ptPos;
    vs_out.ptColor = ptColor;
}
