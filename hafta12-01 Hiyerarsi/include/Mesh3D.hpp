#ifndef Mesh3D_hpp
#define Mesh3D_hpp

#include<glm/mat4x4.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<vector>
#include "VertexArrayObject.hpp"
#include <string>
class ShaderProgram;
class MeshManager;
class GuiControl;

class Mesh3D
{
public:
    void rotate(float angle);
    void setPosition(const glm::vec3& pos);
    void setRoll(float angle);
    void setYaw(float angle);
    void setPitch(float pitch);
    void setColor(const glm::vec4& color);
    void setScale(const glm::vec3& scale);
    void setAngles(const glm::vec3& angles);
    void draw();
    void update();
    bool getColorActive();
    void setColorActive(bool active);
    void setTextureShader(ShaderProgram* shader);
    void setColorShader(ShaderProgram* shader);
    void setTexture(unsigned int id);
    void addChild(Mesh3D* child);
private:
    std::string         name;
    Mesh3D();
    bool                colorActive;
    glm::mat4           mtxWorld;
    glm::mat4           mtxCombinedWorld;
    glm::vec3           position;
    glm::vec3           scale;
    glm::vec4           color;
    float               roll;//z
    float               pitch;//x
    float               yaw; //y
    unsigned int        texture;
    VertexArrayObject   vertexArrayObject;  
    friend MeshManager;
    friend GuiControl;
    ShaderProgram*      programColor;
    ShaderProgram*      programTexture;
    Mesh3D* parent;
    std::vector<Mesh3D*> childs;
    bool                isSelected;


};
typedef std::vector<Mesh3D*> Mesh3DList;
#endif