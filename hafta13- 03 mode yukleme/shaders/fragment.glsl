#version 330 core
out vec4 fragColor;
in vec2 texCoords;
in vec3 fragPos;
in vec3 normal;



uniform sampler2D ourTexture;

void main()
{
        vec4 ambient =vec4(0.2,0.2,0.2,1.0);
        vec3 lightPos = vec3(5.0,5.0,5.0);

        vec4 diffuse = vec4(1.0,1.0,1.0,1.0);
        
        vec3 lightDir= normalize(lightPos-fragPos);

        float nLDot= max(dot(normal,lightDir),0.0);

        vec4 diffuseColor=diffuse*nLDot;

        fragColor = (diffuseColor+ambient)*texture(ourTexture,texCoords);

   
}