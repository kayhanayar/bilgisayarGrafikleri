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
#include "VertexTypes.hpp"
#include "utilityFuncitons.hpp"
ShaderProgram program;
GuiControl imguiWindow;
Timer timer;

unsigned int vertexArrayObjectId;
unsigned int indexCount;

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
    unsigned int indexBufferId;
    int vertexCount = 360.0f/angle;
    
    ColoredVertexList vertices(vertexCount);
    IndexList   indices(vertexCount*3);
    indexCount = vertexCount*3;

    glm::vec3 v0;
   
    for(int i=0;i<vertexCount;i++)
    {
        float nextAngle = glm::radians(i*angle);
        v0.x = glm::cos(nextAngle)*radius;
        v0.y = glm::sin(nextAngle)*radius;
        v0.z = 1.0f;
        glm::vec4 color = randomColor(); 
        vertices[i]= {v0,color};
    }
    for(int i=0;i<vertexCount-2;i++)
    {
        indices[i*3]=0;
        indices[i*3+1]=i+1;
        indices[i*3+2]=i+2;
    }
    
    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(ColoredVertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(ColoredVertex),0);
    glVertexAttribPointer(1,4,GL_FLOAT,false,sizeof(ColoredVertex),(const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 
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
    glDrawElements(GL_TRIANGLES,indexCount,GL_UNSIGNED_INT,0);
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