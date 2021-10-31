#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Timer.hpp"
#include "FileLoader.hpp"
#include "ShaderProgram.hpp"
#include "GuiControl.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"

ShaderProgram program;
GuiControl imguiWindow;
Timer timer;

unsigned int vertexArrayObjectId;
unsigned int daireNoktaSayisi;

glm::vec4 color1(1.0f,1.0,0.0,1.0f);
glm::vec4 color2(1.0f,0.0f,0.0f,1.0f);
glm::mat3 mtxTransform;
glm::vec2 vecMove;
float angle;

unsigned int daireOlustur(float angle)
{
  
    float radius= 0.5;
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    int vertexCount = 360.0f/angle;
    
    std::vector<glm::vec3> vertices(vertexCount*3);
    daireNoktaSayisi = vertexCount*3;

    glm::vec3 v0(0.0f,0.0f,1.0f),v1,v2;
    
    for(int i=0;i<vertexCount;i++)
    {
        float nextAngle = glm::radians(i*angle);
        v1.x = glm::cos(nextAngle)*radius;
        v1.y = glm::sin(nextAngle)*radius;
        v1.z = 1.0f;
        nextAngle = glm::radians((i+1)*angle);
        v2.x = glm::cos(nextAngle)*radius;
        v2.y = glm::sin(nextAngle)*radius;
        v2.z = 1.0f;       
        vertices[i*3]= v0;
        vertices[i*3+1]= v1;
        vertices[i*3+2]= v2;
    }
   
    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertexCount*3,&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(float)*3,0);
    glEnableVertexAttribArray(0);  

    return vertexArrayObjectId;  
}
void keyboard_callback(GLFWwindow* window,int key,int scanCode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    
    if(key==GLFW_KEY_LEFT)
        vecMove.x-=0.1;
    if(key==GLFW_KEY_RIGHT)
        vecMove.x+=0.1;
    if(key==GLFW_KEY_UP)
        vecMove.y+=0.1;
    if(key==GLFW_KEY_DOWN)
        vecMove.y-=0.1;   
        
}
void ciz()
{
    double elapsedTime = timer.elapsedSeconds();
    if(elapsedTime<0.016)
    {
        unsigned int miliseconds = (0.016-elapsedTime)*1000;
        angle+=1;
        timer.sleep(miliseconds);
    }
    glClearColor(0.3,0.4,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    program.use();     
    glBindVertexArray(vertexArrayObjectId);
    
    glm::mat3 mtxRotate = glm::rotate(glm::mat3(1),glm::radians(angle));
    glm::mat3 mtxTranslate = glm::translate(glm::mat3(1),vecMove);
    mtxTransform = mtxTranslate*mtxRotate;
    program.setMat3("uMtxTransform",mtxTransform);
    program.setVec4("uColor",color1);
    glDrawArrays(GL_TRIANGLES,0,daireNoktaSayisi);
    imguiWindow.createFrame();
    imguiWindow.createFrameItems();
    imguiWindow.draw();
    
}
int main()
{

    glm::vec3 n1(2.0,3.0,1.0);
    
    if(!glfwInit())
    return -1;

    GLFWwindow* window = glfwCreateWindow(500,500,"ilk program",0,0);
    if(window==nullptr)
    {
        std::cout<<"pencere olusmadi"<<std::endl;
        glfwTerminate();
        return -1;        
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,(GLFWkeyfun)keyboard_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"glad yukleme hatasi"<<std::endl;
    }
    program.attachShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uMove");
    program.addUniform("uColor");
    program.addUniform("uMtxTransform");

    vertexArrayObjectId = daireOlustur(10);

    imguiWindow.init(window);

    timer.start();
    mtxTransform = glm::mat3(1);

    
   
    while(!glfwWindowShouldClose(window))
    {


        glfwPollEvents();
        ciz();
        glfwSwapBuffers(window);
        
    }




    
}