#ifndef UtilityFuncitons_hpp
#define UtilityFuncitons_hpp
#include<glm/vec4.hpp>
#include<iostream>
#include<glm/mat4x4.hpp>
glm::vec4 randomColor();
std::ostream& operator<<(std::ostream&os,const glm::mat4& matrix);

#endif