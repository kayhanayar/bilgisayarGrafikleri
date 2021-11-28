
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <stb/stb_image.h>
#include "Timer.hpp"
#include "FileLoader.hpp"
#include "ShaderProgram.hpp"
#include "GuiControl.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexTypes.hpp"
#include "MeshManager.hpp"
#include "Mesh2D.hpp"
using namespace std;
ShaderProgram program;
GuiControl imguiWindow;
unsigned int textureId;
Timer timer;

MeshManager meshManager;
Mesh2D * c1;
Mesh2D * c2;


glm::mat4 mtxTransform;
glm::mat4 mtxView;
glm::mat4 mtxProj;
glm::vec3 vecMove;
float angle;

void sekilOlustur(SHAPETYPE type)
{
    if(type==SHAPE_CIRCLE)
    {
        std::cout<<"SHAPE_CIRCLE"<<std::endl;
    }
    if(type==SHAPE_SQUARE)
    {
        std::cout<<"SHAPE_SQUARE"<<std::endl;
    }
        if(type==SHAPE_TRIANGLE)
    {
        std::cout<<"SHAPE_TRIANGLE"<<std::endl;
    }    
}
unsigned int kareOlustur()
{
    unsigned int vertexArrayObjectId;
    int vertexCount = 4;
    
    TexturedVertexList vertices(vertexCount);
    IndexList   indices(6);
    //indexCount = 6;

    vertices[0].pos = glm::vec3(-0.5,-0.5,1.0f);
    vertices[1].pos = glm::vec3( 0.5,-0.5,1.0f);
    vertices[2].pos = glm::vec3( 0.5, 0.5,1.0f);
    vertices[3].pos = glm::vec3(-0.5, 0.5,1.0f);

    vertices[0].tex = glm::vec2( 0.0f, 0.0f);
    vertices[1].tex = glm::vec2( 1.0f, 0.0f);
    vertices[2].tex = glm::vec2( 1.0f, 1.0f);
    vertices[3].tex = glm::vec2(0.0f, 1.0f);

    indices[0]= 0;  indices[1]= 1; indices[2]= 2;
    indices[3]= 0;  indices[4]= 2; indices[5]= 3;

   // vertexArrayObjectId =  createTextureBuffer(vertices,indices);

    return vertexArrayObjectId;

}

unsigned int loadTexture(std::string fileName)
{
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    int width,height,nrChannels;
    auto data = stbi_load(fileName.c_str(),&width,&height,&nrChannels,0);
  
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return id;
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
void initScene(GLFWwindow* window)
{
    program.attachShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uMtxTransform");
    program.addUniform("uMtxView");
    program.addUniform("uMtxProj");
    imguiWindow.setPos(&vecMove);
    imguiWindow.setAngle(&angle);
    imguiWindow.tiklaSekilOlustur= sekilOlustur;
    c1= meshManager.createCircle();
    c2= meshManager.createCircle();

    textureId =loadTexture("images/brick.jpg");

    mtxView = glm::lookAt(glm::vec3(0.0f,5.0f,5.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    mtxProj = glm::perspective(glm::radians(90.0f),(900.0f/900.0f),1.0f,100.0f);

    imguiWindow.init(window);

    timer.start();
      
}
void draw()
{
    double elapsedTime = timer.elapsedSeconds();
    if(elapsedTime<0.016)
    {
        unsigned int miliseconds = (0.016-elapsedTime)*1000;

        timer.sleep(miliseconds);
    }
    glClearColor(0.3,0.4,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    program.use();   
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);  
    program.setMat4("uMtxView",mtxView);
    program.setMat4("uMtxProj",mtxProj);
    c1->setPosition(vecMove);
    c1->rotate(1);
    c1->draw(program);
    
    c2->setPosition(-vecMove);
    c2->setAngle(angle);
    c2->draw(program);
}

int main()
{
    if(!glfwInit())    return -1;

    GLFWwindow* window = glfwCreateWindow(1000,900,"ilk program",0,0);
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

    initScene(window); 
   
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        draw();
        imguiWindow.createFrame();
        imguiWindow.createFrameItems();
        imguiWindow.draw();
        glfwSwapBuffers(window);
    }




    
}