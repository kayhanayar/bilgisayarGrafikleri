#ifndef Mesh3D_hpp
#define Mesh3D_hpp

#include<glm/mat4x4.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<vector>
#include "VertexArrayObject.hpp"
class ShaderProgram;
class MeshManager;


class Mesh3D
{
public:
    void rotate(float angle);
    void setPosition(const glm::vec3& pos);
    void setAngle(float angle);
    void setColor(const glm::vec4& color);
    void setScale(const glm::vec3& scale);
    void draw(ShaderProgram& shader);
    void update();
    bool getColorActive();
    void setColorActive(bool active);
private:
    Mesh3D();
    bool                colorActive;
    glm::mat4           mtxWorld;
    glm::vec3           position;
    glm::vec3           scale;
    glm::vec4           color;
    float               angle;
    VertexArrayObject   vertexArrayObject;  
    friend MeshManager;
};
typedef std::vector<Mesh3D*> Mesh3DList;
#endif