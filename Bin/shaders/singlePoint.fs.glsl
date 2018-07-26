#version 420 core

in VS_OUT
{
    vec4 ptPos;
    vec4 ptColor;
} fs_in;

out vec4 color;

void main(void)
{
    color = fs_in.ptColor;
}
