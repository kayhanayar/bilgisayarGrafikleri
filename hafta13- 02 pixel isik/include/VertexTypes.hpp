#ifndef VertexTypes_hpp
#define VertexTypes_hpp
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/vec2.hpp>
#include<vector>
class ColoredVertex
{
public:
    glm::vec3 pos;
    glm::vec4 color;
};

class LightTextureVertex
{
public:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 tex;
};
class TexturedVertex
{
public:
    glm::vec3 pos;
    glm::vec2 tex;
};
typedef std::vector<glm::vec3>          VertexList;
typedef std::vector<ColoredVertex>      ColoredVertexList;
typedef std::vector<unsigned int>       IndexList;
typedef std::vector<TexturedVertex>     TexturedVertexList;
typedef std::vector<LightTextureVertex> LightTextureVertexList;
#endif