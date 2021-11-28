#version 330 core
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoords;
uniform mat4 uMtxTransform;
uniform mat4 uMtxView;
uniform mat4 uMtxProj;
out vec2 texCoords;
void main()
{
    mat4 mtxCombined = uMtxProj*uMtxView*uMtxTransform;
    gl_Position = mtxCombined*vec4(inPosition,1.0);
    texCoords= inTexCoords;
}