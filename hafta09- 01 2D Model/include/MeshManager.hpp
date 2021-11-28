#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
#include "VertexTypes.hpp"
#include "VertexArrayObject.hpp"
class Mesh2D;
class VertexArrayObject;



class MeshManager
{
public:
    Mesh2D* createCircle();
    Mesh2D* createSquare();
private:
    VertexArrayObject createTextureBuffers(TexturedVertexList& vertices,IndexList& indices);
    std::map<std::string,VertexArrayObject> vaoMap;
};


#endif