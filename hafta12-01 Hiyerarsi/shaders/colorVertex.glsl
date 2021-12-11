#version 330 core
layout(location=0) in vec3 inPosition;
uniform mat4 uMtxTransform;
uniform mat4 uMtxView;
uniform mat4 uMtxProj;
void main()
{
    mat4 mtxCombined = uMtxProj*uMtxView*uMtxTransform;
    gl_Position = mtxCombined*vec4(inPosition,1.0);
}