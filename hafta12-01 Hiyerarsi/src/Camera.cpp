#include "Camera.hpp"

#include "ShaderProgram.hpp"
#include"UtilityFuncitons.hpp"
#include <glm/gtx/string_cast.hpp>
#include<glm/gtc/matrix_transform.hpp>
Camera::Camera()
    : roll(0),
      pitch(0),
      yaw(0)
{
    position= glm::vec3(0.0,5.0f,5.0f);
    update();
    
}
void Camera::setPosition(const glm::vec3& pos) 
{
    position = pos;
    update();
}

void Camera::setRoll(float angle)
{
    this->roll = angle;
     update();
}
void Camera::setYaw(float angle)
{
    this->yaw = angle;
     update();
}
void Camera::setPitch(float angle)
{
    this->pitch = angle;
     update();
}
void Camera::setAngles(const glm::vec3& angles)
{
    setRoll(angles.z);
    setPitch(angles.x);
    setYaw(angles.y);
     update();
}
void Camera::moveForward() {
    position+=getLookVector();
    update();
}
void Camera::moveBackWard() {
    position-=getLookVector();
     update();
}
void Camera::moveLeft() {
    position-=getRightVector();
     update();
}
void Camera::moveRight() {
    position+=getRightVector();
     update();
}
void Camera::moveUp() {
    
}
void Camera::moveDown() {
    
}
void Camera::rotateLeft()
{
    yaw+=1;
    update();
}
void Camera::rotateRight()
{
    yaw-=1;
    update();
}
void Camera::rotateUp() {
    if(pitch<90)
        pitch+=1;
    update();
}
void Camera::rotateDown() {
    if(pitch>-90)
     pitch-=1;
     update();
}
glm::vec3 Camera::getLookVector() 
{
    glm::vec3 veclook;
    veclook.x= mtxWorld[2][0];
    veclook.y= mtxWorld[2][1];
    veclook.z= mtxWorld[2][2];
    return -veclook;
    
}
glm::vec3 Camera::getRightVector() {
    glm::vec3 vecRight;
    vecRight.x= mtxWorld[0][0];
    vecRight.y= mtxWorld[0][1];
    vecRight.z= mtxWorld[0][2];
    return vecRight;    
}
glm::mat4 Camera::getViewMatrix() {
    update();
    return mtxView;
}
glm::mat4 Camera::getProjMatrix() {
    update();
    return mtxProj;
}
void Camera::update()
{

    glm::mat4 mtxRotateX = glm::rotate(glm::mat4(1),glm::radians(pitch),glm::vec3(1.0,0.0f,0.0));
    glm::mat4 mtxRotateY = glm::rotate(glm::mat4(1),glm::radians(yaw),glm::vec3(0.0,1.0f,0.0));
    glm::mat4 mtxRotateZ = glm::rotate(glm::mat4(1),glm::radians(roll),glm::vec3(0.0,0.0f,1.0));        
    glm::mat4 mtxRotate = mtxRotateZ*mtxRotateY*mtxRotateX;
    glm::mat4 mtxTranslate = glm::translate(glm::mat4(1),-position);
  
    mtxWorld = mtxTranslate*mtxRotate;
    mtxView = glm::inverse(mtxRotate)*mtxTranslate;
    mtxProj = glm::perspective(glm::radians(90.0f),(900.0f/900.0f),1.0f,100.0f);
    

}

