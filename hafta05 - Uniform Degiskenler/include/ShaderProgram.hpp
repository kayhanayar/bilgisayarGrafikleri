#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp
#include<string>
#include<map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class ShaderProgram
{
public:
    ShaderProgram();
    void attachShader(const std::string& fileName,
                        unsigned int shaderType);
    void addUniform(const std::string& varName);
    void setFloat(const std::string& varName,float value);
    void setVec3(const std::string& varName,const glm::vec3& value);
    void setVec4(const std::string& varName,const glm::vec4& value);
    void link();
    void use();
private:
    std::map<std::string,unsigned int> m_uniformVars;

    unsigned int m_id;
    unsigned int m_vertexSahderId;
    unsigned int m_fragmentShaderId;
};

#endif