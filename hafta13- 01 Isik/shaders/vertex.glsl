#version 330 core
layout(location=0) in vec3 inPosition;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoords;
uniform mat4 uMtxTransform;
uniform mat4 uMtxView;
uniform mat4 uMtxProj;
uniform mat3 uMtxNormal;
out vec2 texCoords;
out vec4 diffuseColor;
void main()
{
    vec4 diffuse = vec4(1.0,1.0,1.0,1.0);
    vec4 lightColor = vec4(1.0,1.0,1.0,1.0);
    vec3 lightPosition = vec3(0.0,0.0,-1.0);
    
    vec3 normal = normalize(uMtxNormal*inNormal);

    vec3 revLightDir = -normalize(lightDir);

    float nLDot= max(dot(normal,revLightDir),0.0);

    diffuseColor=diffuse*nLDot;

    mat4 mtxCombined = uMtxProj*uMtxView*uMtxTransform;
    gl_Position = mtxCombined*vec4(inPosition,1.0);
    texCoords= inTexCoords;
}