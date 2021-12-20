#version 330 core
layout(location=0) in vec3 inPosition;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoords;
uniform mat4 uMtxTransform;
uniform mat4 uMtxView;
uniform mat4 uMtxProj;
uniform mat3 uMtxNormal;

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;
void main()
{
    mat4 mtxCombined = uMtxProj*uMtxView*uMtxTransform;
    
    gl_Position = mtxCombined*vec4(inPosition,1.0);

    normal = normalize(uMtxNormal*inNormal);

    fragPos = vec3(uMtxTransform*vec4(inPosition,1.0));    
    texCoords= inTexCoords;
}