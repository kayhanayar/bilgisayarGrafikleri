#include "UtilityFuncitons.hpp"

glm::vec4 randomColor()
{
    glm::vec4 color;
    color.r = (rand()%256)/256.0f;
    color.g = (rand()%256)/256.0f;
    color.b = (rand()%256)/256.0f;
    color.a = 1.0f;

    return color;
}