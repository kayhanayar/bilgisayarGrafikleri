#include "UtilityFuncitons.hpp"
#include<iomanip>
glm::vec4 randomColor()
{
    glm::vec4 color;
    color.r = (rand()%256)/256.0f;
    color.g = (rand()%256)/256.0f;
    color.b = (rand()%256)/256.0f;
    color.a = 1.0f;

    return color;
}
std::ostream& operator<<(std::ostream&os,const glm::mat4& matrix) 
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
          os<<std::setprecision(2)<<std::setw(10)<<matrix[j][i];
        os<<std::endl;
    }
    os<<"-----------------------------"<<std::endl;
    return os;

}
