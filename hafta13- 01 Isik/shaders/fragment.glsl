#version 330 core
out vec4 fragColor;
in vec2 texCoords;
in vec4 diffuseColor;
uniform sampler2D ourTexture;
void main()
{

        fragColor = texture(ourTexture,texCoords)*diffuseColor;

   
}