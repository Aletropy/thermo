#version 460 core

layout(location = 0) in vec4 v_VertexPosition;

void main()
{
    gl_Position = v_VertexPosition;
}