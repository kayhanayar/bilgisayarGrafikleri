
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
#include "glm/gtx/matrix_transform_2d.hpp"
#include "VertexTypes.hpp"
#include "utilityFuncitons.hpp"
using namespace std;
ShaderProgram program;
GuiControl imguiWindow;
Timer timer;

unsigned int vertexArrayObjectId;
unsigned int textureId;

unsigned int indexCount;


glm::mat3 mtxTransform;
glm::vec2 vecMove;
float angle;

unsigned int createTextureBuffer(TexturedVertexList& vertices,IndexList& indices)
{
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    unsigned int indexBufferId;

    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(TexturedVertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(TexturedVertex),0);
    glVertexAttribPointer(1,2,GL_FLOAT,false,sizeof(TexturedVertex),(const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 
    return vertexArrayObjectId;
}

unsigned int kareOlustur()
{
    unsigned int vertexArrayObjectId;
    int vertexCount = 4;
    
    TexturedVertexList vertices(vertexCount);
    IndexList   indices(6);
    indexCount = 6;

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

    vertexArrayObjectId =  createTextureBuffer(vertices,indices);

    return vertexArrayObjectId;

}
unsigned int daireOlustur(float angle)
{
  
    float radius= 0.5;
    unsigned int vertexArrayObjectId;
    int vertexCount = 360.0f/angle;
    
    TexturedVertexList vertices(vertexCount);
    IndexList   indices(vertexCount*3);
    indexCount = vertexCount*3;

    glm::vec3 v0;
   
    for(int i=0;i<vertexCount;i++)
    {
        float nextAngle = glm::radians(i*angle);
        v0.x = glm::cos(nextAngle)*radius;
        v0.y = glm::sin(nextAngle)*radius;
        v0.z = 1.0f;
        glm::vec2 tex = glm::vec2(1,1); 
        vertices[i]= {v0,tex};
    }
    for(int i=0;i<vertexCount-2;i++)
    {
        indices[i*3]=0;
        indices[i*3+1]=i+1;
        indices[i*3+2]=i+2;
    }
    vertexArrayObjectId = createTextureBuffer(vertices,indices);

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

    vertexArrayObjectId = kareOlustur();
    textureId =loadTexture("images/brick.jpg");
    cout<<textureId<<endl;
    imguiWindow.init(window);

    timer.start();
      
}
void draw()
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);  
    glBindVertexArray(vertexArrayObjectId);
    

    glm::mat3 mtxRotate = glm::rotate(glm::mat3(1),glm::radians(angle));
    glm::mat3 mtxTranslate = glm::translate(glm::mat3(1),vecMove);
    mtxTransform = mtxTranslate*mtxRotate;


    program.setMat3("uMtxTransform",mtxTransform);
    glDrawElements(GL_TRIANGLES,indexCount,GL_UNSIGNED_INT,0);

    
}

int main()
{
    if(!glfwInit())    return -1;

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