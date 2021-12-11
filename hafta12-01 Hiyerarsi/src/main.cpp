
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
#include "UtilityFuncitons.hpp"
#include "MeshManager.hpp"
#include "Mesh3D.hpp"
#include "Camera.hpp"
using namespace std;
ShaderProgram programTexture;
ShaderProgram programColor;
GuiControl imguiWindow;
unsigned int textureId;
Timer timer;

MeshManager meshManager;

Mesh3D * cube;
Mesh3D* grid;
Camera* camera;
Mesh3D* cube2;

glm::mat4 mtxTransform;


glm::vec3 vecMove;
glm::vec3 angles;

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
    if(key==GLFW_KEY_W)
        camera->moveForward();
    if(key==GLFW_KEY_S)
        camera->moveBackWard();        
    if(key==GLFW_KEY_A)
        camera->moveLeft();
    if(key==GLFW_KEY_D)
        camera->moveRight();           
    if(key==GLFW_KEY_LEFT)
        camera->rotateLeft();
    if(key==GLFW_KEY_RIGHT)
        camera->rotateRight();
    if(key==GLFW_KEY_UP)
        camera->rotateUp();
    if(key==GLFW_KEY_DOWN)
        camera->rotateDown();
    
        
}
void initScene(GLFWwindow* window)
{
    programTexture.attachShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    programTexture.attachShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    programTexture.link();
    programTexture.addUniform("uMtxTransform");
    programTexture.addUniform("uMtxView");
    programTexture.addUniform("uMtxProj");


    programColor.attachShader("./shaders/colorVertex.glsl",GL_VERTEX_SHADER);
    programColor.attachShader("./shaders/colorFragment.glsl",GL_FRAGMENT_SHADER);
    programColor.link();
    programColor.addUniform("uMtxTransform");
    programColor.addUniform("uMtxView");
    programColor.addUniform("uMtxProj");
    programColor.addUniform("uColor");

   
    imguiWindow.setPos(&vecMove);
    imguiWindow.setAngle(&angles);
    imguiWindow.tiklaSekilOlustur= sekilOlustur;

    cube = meshManager.createCube();

    cube->setTextureShader(&programTexture);
    cube->setColorShader(&programColor);


    grid = meshManager.createGrid();
   
    grid->setColorShader(&programColor);

    cube->addChild(grid);
    grid->setColorActive(true);
    grid->setColor({1.0,0.0,0.0,1.0});
    
    camera = new Camera();
    textureId =loadTexture("images/brick.jpg");
    cube->setTexture(textureId);
    imguiWindow.setRoot(cube);
    programTexture.setCamera(camera);
    programColor.setCamera(camera); 
    imguiWindow.init(window);

    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);   

    cube->setPosition(vecMove);

    cube->draw(); 
   
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