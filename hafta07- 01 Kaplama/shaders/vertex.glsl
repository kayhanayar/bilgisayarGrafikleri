#version 330 core
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoords;
uniform mat3 uMtxTransform;
out vec2 texCoords;
void main()
{
    gl_Position = vec4(uMtxTransform*inPosition,1.0);
    texCoords= inTexCoords;
}