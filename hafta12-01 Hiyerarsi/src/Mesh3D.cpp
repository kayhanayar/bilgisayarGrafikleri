#include "Mesh3D.hpp"
#include "ShaderProgram.hpp"
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<glad/glad.h>
Mesh3D::Mesh3D()
{
    position=glm::vec3(0.0f,0.0f,0.0f);
    scale = glm::vec3(1.0f,1.0f,1.0f);
    color = glm::vec4(1.0f,0.0f,1.0f,1.0f);
    mtxCombinedWorld = glm::mat4(1);
    mtxWorld = glm::mat4(1);
    yaw= 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
    colorActive = false;
    parent = 0;
    programTexture =0;
    programColor = 0;
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
void Mesh3D::setColorShader(ShaderProgram* shader)
{
    programColor = shader;
}
void Mesh3D::setTextureShader(ShaderProgram* shader) {
    programTexture= shader;
}
void Mesh3D::setTexture(unsigned int id) {
    texture=id;
}
void Mesh3D::addChild(Mesh3D* child) {
    childs.push_back(child);
    child->parent = this;
    child->update();
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

    if(parent)
        mtxCombinedWorld= parent->mtxCombinedWorld*mtxWorld;
    else 
        mtxCombinedWorld=mtxWorld;
    for(auto next:childs)
        next->update();

}
void Mesh3D::rotate(float angle)
{

    update();
}
void Mesh3D::draw()
{
    if(colorActive||programTexture==0)
    {
        programColor->use();
        programColor->setMat4("uMtxTransform",mtxCombinedWorld);
        programColor->setVec4("uColor",color);
    }
    else
    {
        programTexture->use();
        programTexture->setMat4("uMtxTransform",mtxCombinedWorld);
        
    }
    vertexArrayObject.use();
    vertexArrayObject.draw();
    vertexArrayObject.unuse();
    
    for(auto next:childs)
       next->draw();
}