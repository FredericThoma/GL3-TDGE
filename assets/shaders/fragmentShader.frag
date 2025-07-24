#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform bool u_UseTexture;

out vec4 FragColor;

void main() {
        if (u_UseTexture) {
                vec4 texColor = texture(u_Texture, v_TexCoord);
                FragColor = texColor * u_Color;
        } else {
                FragColor = u_Color;
        }
}
