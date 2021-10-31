#version 330 core
out vec4 fragColor;
in vec4 outColor;
uniform vec4 uColor;
void main()
{
    fragColor = outColor;
}