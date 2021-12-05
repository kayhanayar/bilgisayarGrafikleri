#ifndef Camera_hpp
#define Camera_hpp
#include<glm/mat4x4.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<vector>
class ShaderProgram;
class Camera
{
public:
    Camera();
    ~Camera();
    void setPosition(const glm::vec3& pos);
    void setRoll(float angle);
    void setYaw(float angle);
    void setPitch(float pitch);
    void setCamera(ShaderProgram& program);
    void setAngles(const glm::vec3& angles);
    void moveForward();
    void moveBackWard();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();
    glm::vec3 getLookVector();
    glm::vec3 getRightVector();
private:
    void            update();
    glm::mat4           mtxWorld;
    glm::mat4           mtxView;
    glm::mat4           mtxProj;
    glm::vec3           position;
    float               roll;//z
    float               pitch;//x
    float               yaw; //y
};



#endif