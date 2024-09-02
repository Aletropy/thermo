#version 460 core

layout(location = 0) in vec2 a_TexCoords;
layout(location = 1) in float a_TexIndex;
layout(location = 2) in float a_TillingFactor;
layout(location = 3) in vec4 a_VertexColor;

out vec4 fragColor;

uniform sampler2D u_Textures[16];

void main()
{
    if(a_TexIndex < 0.0)
    {
        fragColor = a_VertexColor;
        return;
    }

    int texIndex = int(a_TexIndex);
    fragColor = texture(u_Textures[texIndex], a_TexCoords * a_TillingFactor) * a_VertexColor;
}