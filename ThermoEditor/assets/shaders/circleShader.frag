#version 460 core

in vec4 a_VertexColor;

out vec4 fragColor;

void main()
{
    fragColor = a_VertexColor;
}