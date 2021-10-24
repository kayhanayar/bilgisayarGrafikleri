#include<iostream>
#include "kutuphane.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "Timer.hpp"
#include "FileLoader.hpp"
#include "ShaderProgram.hpp"
#include "GuiControl.hpp"

ShaderProgram program;
GuiControl imguiWindow;
unsigned int vertexBufferId;
unsigned int vertexArrayObjectId;
glm::vec3 vecMove;
Timer timer;
float vertices[]=
{
    -0.5,-0.5,0.0,
    0.0f,0.0,0.0,
    0.5,-0.5,0.0,
    -0.5,0.5,0.0,
    0.0f,0.0f,0.0f,
    0.5f,0.5f,0.0
};


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
    
    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(float)*3,0);
    glEnableVertexAttribArray(0);

    imguiWindow.init(window);
    glm::vec4 color1(1.0f,1.0,0.0,1.0f);
    glm::vec4 color2(1.0f,0.0f,0.0f,1.0f);
    timer.start();
    while(!glfwWindowShouldClose(window))
    {


        glfwPollEvents();
        double elapsedTime = timer.elapsedSeconds();
        if(elapsedTime<0.016)
        {
            unsigned int miliseconds = (0.016-elapsedTime)*1000;
           
            timer.sleep(miliseconds);
        }
        glClearColor(0.3,0.4,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        vecMove.x+=0.01;
        program.use();
    
        glBindVertexArray(vertexArrayObjectId);
        program.setVec3("uMoveX",vecMove);
        program.setVec4("uColor",color1);
        glDrawArrays(GL_TRIANGLES,0,3);
        program.setVec4("uColor",color2);
        glDrawArrays(GL_TRIANGLES,3,6);

        imguiWindow.createFrame();
        imguiWindow.createFrameItems();
        imguiWindow.draw();
    
            
          


        

        glfwSwapBuffers(window);
        
    }




    
}