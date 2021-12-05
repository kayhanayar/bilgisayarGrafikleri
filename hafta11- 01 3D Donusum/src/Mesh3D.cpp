#include "Mesh3D.hpp"
#include "ShaderProgram.hpp"
#include<glm/gtc/matrix_transform.hpp>


Mesh3D::Mesh3D()
{
    position=glm::vec3(0.0f,0.0f,0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    yaw= 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
    colorActive = false;
    update();
}
bool Mesh3D::getColorActive()
{
    return colorActive;
}
void Mesh3D::setColorActive(bool active)
{
    colorActive = active;
}
void Mesh3D::setColor(const glm::vec4& color)
{
    this->color = color;
 
}
void Mesh3D::setPosition(const glm::vec3& pos)
{
    this->position = pos;
    update();
}
void Mesh3D::setScale(const glm::vec3& scale)
{
    this->scale = scale;
    update();
}
void Mesh3D::setAngles(const glm::vec3& angles)
{
    setRoll(angles.z);
    setPitch(angles.x);
    setYaw(angles.y);
     update();
}
void Mesh3D::setRoll(float angle)
{
    this->roll = angle;
     update();
}
void Mesh3D::setYaw(float angle)
{
    this->yaw = angle;
     update();
}
void Mesh3D::setPitch(float angle)
{
    this->pitch = angle;
     update();
}
void Mesh3D::update()
{

    glm::mat4 mtxRotateX = glm::rotate(glm::mat4(1),glm::radians(pitch),glm::vec3(1.0,0.0f,0.0));
    glm::mat4 mtxRotateY = glm::rotate(glm::mat4(1),glm::radians(yaw),glm::vec3(0.0,1.0f,0.0));
    glm::mat4 mtxRotateZ = glm::rotate(glm::mat4(1),glm::radians(roll),glm::vec3(0.0,0.0f,1.0));        
    glm::mat4 mtxRotate = mtxRotateX*mtxRotateY*mtxRotateZ;
    glm::mat4 mtxTranslate = glm::translate(glm::mat4(1),position);
    glm::mat4 mtxScale = glm::scale(glm::mat4(1),scale);
    mtxWorld = mtxTranslate*mtxRotate*mtxScale;

}
void Mesh3D::rotate(float angle)
{

    update();
}
void Mesh3D::draw(ShaderProgram& program)
{
    program.setMat4("uMtxTransform",mtxWorld);
    vertexArrayObject.use();
    vertexArrayObject.draw();
    vertexArrayObject.unuse();
}