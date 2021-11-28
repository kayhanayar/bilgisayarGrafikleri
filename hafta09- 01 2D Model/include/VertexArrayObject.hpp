#ifndef VertexArrayObject_hpp
#define VertexArrayObject_hpp
#include<vector>
class MeshManager;
class Mesh2D;
class VertexArrayObject
{
public:
    VertexArrayObject();
    void use();
    void draw();
    void unuse();
private:
    
    unsigned int indexCount;
    unsigned int id;
    friend MeshManager;
    friend Mesh2D;
};


#endif