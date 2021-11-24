#ifndef GuiControl_hpp
#define GuiControl_hpp
#include <glm/vec2.hpp>
#include <functional>
class GLFWwindow;

enum SHAPETYPE
{
    SHAPE_SQUARE=0,
    SHAPE_CIRCLE=1,
    SHAPE_HEXAGON=2,
    SHAPE_TRIANGLE=3    
};

typedef std::function<void(SHAPETYPE)>  SekilOlusturFonksiyonu;
class GuiControl
{
public:
    GuiControl();
    void init(GLFWwindow* window);
    void createFrame();
    void createFrameItems();
    void draw();
    void setPos(glm::vec2* pos);
    void setAngle(float *angle);
    SekilOlusturFonksiyonu tiklaSekilOlustur;
private:
    int secilenSekil;
    glm::vec2* vecPos;
    float*  angle;
};

#endif