#ifndef GuiControl_hpp
#define GuiControl_hpp
class GLFWwindow;
class GuiControl
{
public:
    GuiControl();
    void init(GLFWwindow* window);
    void createFrame();
    void createFrameItems();
    void draw();

private:
};

#endif