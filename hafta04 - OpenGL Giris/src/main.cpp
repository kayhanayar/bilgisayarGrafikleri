#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>

#include "FileLoader.hpp"
unsigned int fragmentShaderId;
unsigned int vertexShaderId;
unsigned int shaderProgramId;
unsigned int vertexBufferId;
unsigned int vertexArrayObjectId;

float vertices[]= {
    -0.5f,-0.5f,0.0f,
     0.5f,-0.5f,0.0f,
     0.0f, 0.5f,0.0f
};

void imgui_olustur(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsClassic();

}
void imgui_pencereOlustur()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void imgui_pencereElemanlari()
{
    
        ImGui::Begin("imgui penceresi");
        if(ImGui::Button("Tikla Beni"))
        {
            std::cout<<"tikladin"<<std::endl;
        }
        ImGui::End();
}
void imgui_ciz()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"glad yukleme hatasi"<<std::endl;
    }

    std::string strVsSource = FileLoader::readRawFromFile("./shaders/vertex.glsl");
    std::string strFsSource = FileLoader::readRawFromFile("./shaders/fragment.glsl");
    const char   * vsSource = &strVsSource[0];
    const char   *fsSource = &strFsSource[0];
   
    vertexShaderId= glCreateShader(GL_VERTEX_SHADER);   
    glShaderSource(vertexShaderId,1,&(vsSource),0);
    glCompileShader(vertexShaderId);

    int isCompiled;
    char message[512];
    glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS,&isCompiled);

    if(!isCompiled)
    {
        glGetShaderInfoLog(vertexShaderId,512,0,message);
        std::cout<<"VertexShader:"<<message<<std::endl;
    }

    fragmentShaderId= glCreateShader(GL_FRAGMENT_SHADER);   
    glShaderSource(fragmentShaderId,1,&(fsSource),0);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId,GL_COMPILE_STATUS,&isCompiled);

    if(!isCompiled)
    {
        glGetShaderInfoLog(fragmentShaderId,512,0,message);
        std::cout<<"FramentShader:"<<message<<std::endl;
    }

    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId,vertexShaderId);
    glAttachShader(shaderProgramId,fragmentShaderId);//fragmentShaderId ile shaderProgramId aynı değere sahip
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId,GL_LINK_STATUS,&isCompiled);

    if(!isCompiled)
    {
        glGetProgramInfoLog(shaderProgramId,512,0,message);
        std::cout<<"Program:"<<message<<std::endl;
    }


    glGenVertexArrays(1,&vertexArrayObjectId);
    glGenVertexArrays(1,&vertexBufferId);

    glBindVertexArray(vertexArrayObjectId);

    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,false,3*sizeof(float),0);
    glEnableVertexAttribArray(0);



    imgui_olustur(window);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.3,0.4,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);

        glBindVertexArray(vertexArrayObjectId);
        glDrawArrays(GL_TRIANGLES,0,3);

        imgui_pencereOlustur();
        imgui_pencereElemanlari();
        imgui_ciz();       
        glfwSwapBuffers(window);
    }




    
}