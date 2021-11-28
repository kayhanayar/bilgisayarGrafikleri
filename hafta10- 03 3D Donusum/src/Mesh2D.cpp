#include "Mesh2D.hpp"
#include "ShaderProgram.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include<glm/mat3x3.hpp>
Mesh2D::Mesh2D()
{
    position=glm::vec2(0.0f,0.0f);
    scale = glm::vec2(1.0f,1.0f);
    angle= 0.0f;
    
    colorActive = false;
    update();
}
bool Mesh2D::getColorActive()
{
    return colorActive;
}
void Mesh2D::setColorActive(bool active)
{
    colorActive = active;
}
void Mesh2D::setColor(const glm::vec4& color)
{
    this->color = color;
 
}
void Mesh2D::setPosition(const glm::vec2& pos)
{
    this->position = pos;
    update();
}
void Mesh2D::setScale(const glm::vec2& scale)
{
    this->scale = scale;
     update();
}
void Mesh2D::setAngle(float angle)
{
    this->angle = angle;
     update();
}
void Mesh2D::update()
{
    glm::mat4 mtxRotate = glm::rotate(glm::mat4(1),glm::radians(angle),glm::vec3(0.0,0.0,1.0));
    glm::mat4 mtxTranslate = glm::translate(glm::mat4(1),glm::vec3(position.x,position.y,1.0f));
    glm::mat4 mtxScale = glm::scale(glm::mat4(1),glm::vec3(scale.x,scale.y,1.0f));
    mtxWorld = mtxTranslate*mtxRotate*mtxScale;

}
void Mesh2D::rotate(float angle)
{
    if(this->angle>360)
    {
        this->angle=360-this->angle;
    }
    this->angle+=angle;
    update();
}
void Mesh2D::draw(ShaderProgram& program)
{
    program.setMat4("uMtxTransform",mtxWorld);
   
    vertexArrayObject.use();
    vertexArrayObject.draw();
    vertexArrayObject.unuse();
}