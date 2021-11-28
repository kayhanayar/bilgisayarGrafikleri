#include "MeshManager.hpp"
#include "Mesh2D.hpp"
#include<glm/glm.hpp>
#include<glad/glad.h>
Mesh2D* MeshManager::createCircle()
{
    VertexArrayObject vao;
    if(!vaoMap.count("circle"))
    {

        float radius= 0.5;
        float angle = 10;
        unsigned int vertexArrayObjectId;
        int vertexCount = 360.0f/angle;
        
        TexturedVertexList vertices(vertexCount);
        IndexList   indices(vertexCount*3);
        

        glm::vec3 v0;
    
        for(int i=0;i<vertexCount;i++)
        {
            float nextAngle = glm::radians(i*angle);
            v0.x = glm::cos(nextAngle)*radius;
            v0.y = glm::sin(nextAngle)*radius;
            v0.z = 1.0f;
            glm::vec2 tex;
            tex.x = glm::cos(nextAngle)*0.5f+0.5f;
            tex.y = glm::sin(nextAngle)*0.5f+0.5f;   
            vertices[i]= {v0,tex};
        }
        for(int i=0;i<vertexCount-2;i++)
        {
            indices[i*3]=0;
            indices[i*3+1]=i+1;
            indices[i*3+2]=i+2;
        }
        vao = createTextureBuffers(vertices,indices);
        vaoMap["circle"] = vao;
    }
    else
    {
        vao = vaoMap["circle"];
    }
    Mesh2D *mesh= new Mesh2D;
    mesh->vertexArrayObject = vao;

    return mesh;
}
VertexArrayObject MeshManager::createTextureBuffers(TexturedVertexList& vertices,IndexList& indices)
{
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    unsigned int indexBufferId;

    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(TexturedVertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(TexturedVertex),0);
    glVertexAttribPointer(1,2,GL_FLOAT,false,sizeof(TexturedVertex),(const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 


    VertexArrayObject vao;
    vao.indexCount = indices.size();
    vao.id= vertexArrayObjectId;
    return vao;
}