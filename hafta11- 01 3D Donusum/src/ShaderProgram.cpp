#include "ShaderProgram.hpp"
#include "FileLoader.hpp"
#include<glad/glad.h>
#include<iostream>
ShaderProgram::ShaderProgram()
{
    m_id = -1;
}
void ShaderProgram::attachShader(const std::string& fileName,
                                unsigned int shaderType)
{
    if(m_id==-1)
        m_id = glCreateProgram();  
    
    std::string strVsCode = FileLoader::getRawData(fileName);
    const char * vsCode = &strVsCode[0];
    
    unsigned int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId,1,&vsCode,0);
    glCompileShader(shaderId);

    int isCompiled;
    char  message[512];

    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&isCompiled);

    std::string shaderTypeName;

    if(shaderType==GL_VERTEX_SHADER)
        shaderTypeName = "VertexShader :";
    else if(shaderType==GL_FRAGMENT_SHADER)
        shaderTypeName = "FragmentShader";

    if(!isCompiled)
    {
        glGetShaderInfoLog(shaderId,512,0,message);
        
        std::cout<<shaderTypeName<<message<<std::endl;
    }
    else
    {
        glAttachShader(m_id,shaderId);
        m_vertexSahderId = shaderId;
    }
                                
}
void ShaderProgram::link()
{
    glLinkProgram(m_id);

    int isLinked;
    glGetProgramiv(m_id,GL_LINK_STATUS,&isLinked);

    if(!isLinked)
    {
        std::cout<<"shader program cannot linked"<<std::endl;
    }
}
void ShaderProgram::use()
{
    glUseProgram(m_id);
}
void ShaderProgram::addUniform(const std::string& varName)
{
    m_uniformVars[varName] = glGetUniformLocation(m_id,varName.c_str()); 
}
void ShaderProgram::setFloat(const std::string& varName,float value)
{
    glUniform1f(m_uniformVars[varName],value);
}
void ShaderProgram::setVec3(const std::string& varName,const glm::vec3& value)
{
    glUniform3f(m_uniformVars[varName],value.x,value.y,value.z);
}
void ShaderProgram::setVec4(const std::string& varName,const glm::vec4& value)
{
    glUniform4f(m_uniformVars[varName],value.x,value.y,value.z,value.w);
}
void ShaderProgram::setMat3(const std::string& varName,const glm::mat3& value)
{
    glUniformMatrix3fv(m_uniformVars[varName],1,false,&value[0][0]);
}
void ShaderProgram::setMat4(const std::string& varName,const glm::mat4& value)
{
    glUniformMatrix4fv(m_uniformVars[varName],1,false,&value[0][0]);
}