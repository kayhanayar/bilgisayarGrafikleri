#include "GuiControl.hpp"
#include "Mesh3D.hpp"
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
#include<iostream>

GuiControl::GuiControl()
{
    root= 0;
}
void GuiControl::init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsClassic();
}
void GuiControl::createFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiControl::setAngle(glm::vec3* angles)
{
    this->vecAngles = angles;
  
}
void GuiControl::setRoot(Mesh3D* root) {
    this->root = root;
}
void GuiControl::agacaEkle() {
    if(ImGui::TreeNode("Hiyerarsi"))
    {
        agacaEkle(root);
        ImGui::TreePop();
        ImGui::Separator();        
    }
}
void GuiControl::agacaEkle(Mesh3D* aktif) 
{
    if(aktif)
    {
        ImGui::Checkbox(aktif->name.c_str(),&aktif->colorActive);
        if(aktif->childs.size()==0)
            return ;
        if(ImGui::TreeNode("cocuklar"))
        {
            for(auto next:aktif->childs)
            {
                agacaEkle(next);
            }

            ImGui::TreePop();
            ImGui::Separator();        
        }
        
    }   
}
void GuiControl::setPos(glm::vec3* pos)
{
    this->vecPos = pos;
}
void GuiControl::createFrameItems()
{
    ImGui::Begin("imgui penceresi");
    ImGui::SliderFloat3("dondurme",(float*)vecAngles,0,360);
    ImGui::SliderFloat3("hareket",(float*)vecPos,-5.0f,5.0f);

    ImGui::RadioButton("Kare",&secilenSekil,0);ImGui::SameLine();
    ImGui::RadioButton("Daire",&secilenSekil,1);ImGui::SameLine();
    ImGui::RadioButton("Altigen",&secilenSekil,2);ImGui::SameLine();
    ImGui::RadioButton("Ucgen",&secilenSekil,3);   

    if(ImGui::Button("Tikla Beni"))
    {

        tiklaSekilOlustur((SHAPETYPE)secilenSekil);
    }
    agacaEkle();
    ImGui::End();
}
void GuiControl::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
