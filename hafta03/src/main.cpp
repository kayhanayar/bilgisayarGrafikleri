#include<iostream>
#include "kutuphane.hpp"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
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

    
    imgui_olustur(window);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.3,0.4,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        imgui_pencereOlustur();
        imgui_pencereElemanlari();
        imgui_ciz();       
        glfwSwapBuffers(window);
    }




    
}