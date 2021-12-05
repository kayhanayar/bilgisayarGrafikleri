#version 330 core
out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D ourTexture;
void main()
{
    fragColor = texture(ourTexture,texCoords);
}