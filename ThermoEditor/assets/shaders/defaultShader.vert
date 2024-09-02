#version 460 core

layout(location = 0) in vec4 v_VertexPosition;
layout(location = 1) in vec2 v_TexCoords;
layout(location = 2) in float v_TexIndex;
layout(location = 3) in float v_TillingFactor;
layout(location = 4) in vec4 v_VertexColor;

layout(location = 0) out vec2 a_TexCoords;
layout(location = 1) out float a_TexIndex;
layout(location = 2) out float a_TillingFactor;
layout(location = 3) out vec4 a_VertexColor;

uniform mat4 u_ViewProjMatrix;

void main()
{
    gl_Position = u_ViewProjMatrix * v_VertexPosition;
    a_VertexColor = v_VertexColor;
    a_TexCoords = v_TexCoords;
    a_TexIndex = v_TexIndex;
    a_TillingFactor = v_TillingFactor;
}