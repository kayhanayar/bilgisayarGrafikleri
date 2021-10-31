#ifndef VertexTypes_hpp
#define VertexTypes_hpp
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<vector>
class ColoredVertex
{
public:
    glm::vec3 pos;
    glm::vec4 color;
};

typedef std::vector<ColoredVertex>  ColoredVertexList;
typedef std::vector<unsigned int>   IndexList;
#endif