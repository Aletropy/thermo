#version 460 core

layout(location = 0) in vec4 v_VertexPosition;
layout(location = 1) in vec4 v_VertexColor;

out vec4 a_VertexColor;

void main()
{
    gl_Position = v_VertexPosition;
    a_VertexColor = v_VertexColor;
}