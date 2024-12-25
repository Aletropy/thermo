#version 460 core

layout(location = 0) in vec2 a_TexCoords;
layout(location = 1) in float a_TexIndex;
layout(location = 2) in float a_TillingFactor;
layout(location = 3) in vec4 a_VertexColor;

out vec4 fragColor;

uniform sampler2D u_Textures[16];

vec4 getTextureColor(int index, vec2 texCoords, float tilingFactor)
{
    switch (index) {
        case 0: return texture(u_Textures[0], texCoords * tilingFactor);
        case 1: return texture(u_Textures[1], texCoords * tilingFactor);
        case 2: return texture(u_Textures[2], texCoords * tilingFactor);
        case 3: return texture(u_Textures[3], texCoords * tilingFactor);
        case 4: return texture(u_Textures[4], texCoords * tilingFactor);
        case 5: return texture(u_Textures[5], texCoords * tilingFactor);
        case 6: return texture(u_Textures[6], texCoords * tilingFactor);
        case 7: return texture(u_Textures[7], texCoords * tilingFactor);
        case 8: return texture(u_Textures[8], texCoords * tilingFactor);
        case 9: return texture(u_Textures[9], texCoords * tilingFactor);
        case 10: return texture(u_Textures[10], texCoords * tilingFactor);
        case 11: return texture(u_Textures[11], texCoords * tilingFactor);
        case 12: return texture(u_Textures[12], texCoords * tilingFactor);
        case 13: return texture(u_Textures[13], texCoords * tilingFactor);
        case 14: return texture(u_Textures[14], texCoords * tilingFactor);
        case 15: return texture(u_Textures[15], texCoords * tilingFactor);
        default: return vec4(1.0); // Cor padrão (branca)
    }
}

void main()
{
    if(a_TexIndex < 0.0)
    {
        fragColor = a_VertexColor;
        return;
    }

    int texIndex = int(a_TexIndex);
    fragColor = getTextureColor(texIndex, a_TexCoords, a_TillingFactor) * a_VertexColor;
}