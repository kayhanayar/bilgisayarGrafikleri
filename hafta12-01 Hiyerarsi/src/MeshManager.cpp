#include "MeshManager.hpp"
#include "Mesh2D.hpp"
#include "Mesh3D.hpp"
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<iostream>
#include<iomanip>
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
        vao.primitiveType = GL_TRIANGLES;  
    }
    else
    {
        vao = vaoMap["circle"];
    }
    Mesh2D *mesh= new Mesh2D;
    mesh->vertexArrayObject = vao;

    return mesh;
}
Mesh3D* MeshManager::createCube()
{
    VertexArrayObject vao;

    if(!vaoMap.count("cube"))
    {
        unsigned int vertexArrayObjectId;
        int vertexCount = 24;
    
        TexturedVertexList vertices(vertexCount);
        int faceCount= 6;
        IndexList   indices(faceCount*6); 
        glm::vec3 v[8];
        v[0] = glm::vec3(-0.5,0.5,0.5);   
        v[1] = glm::vec3(0.5,0.5,0.5);
        v[2] = glm::vec3(0.5,-0.5,0.5);
        v[3] = glm::vec3(-0.5,-0.5,0.5);
        v[4] = glm::vec3(-0.5,0.5,-0.5);   
        v[5] = glm::vec3(0.5,0.5,-0.5);
        v[6] = glm::vec3(0.5,-0.5,-0.5);
        v[7] = glm::vec3(-0.5,-0.5,-0.5);
        //ön yüz
        vertices[0].pos = v[0]; vertices[0].tex= glm::vec2(0.0,1.0);
        vertices[1].pos = v[1]; vertices[1].tex= glm::vec2(1.0,1.0);
        vertices[2].pos = v[2]; vertices[2].tex= glm::vec2(1.0,0.0);
        vertices[3].pos = v[3]; vertices[3].tex= glm::vec2(0.0,0.0);
        //sağ
        vertices[4].pos = v[1]; vertices[4].tex= glm::vec2(0.0,1.0);
        vertices[5].pos = v[5]; vertices[5].tex= glm::vec2(1.0,1.0);
        vertices[6].pos = v[6]; vertices[6].tex= glm::vec2(1.0,0.0);
        vertices[7].pos = v[2]; vertices[7].tex= glm::vec2(0.0,0.0);  

        //ust
        vertices[8].pos  = v[4]; vertices[8].tex= glm::vec2(0.0,1.0);
        vertices[9].pos  = v[5]; vertices[9].tex= glm::vec2(1.0,1.0);
        vertices[10].pos = v[1]; vertices[10].tex= glm::vec2(1.0,0.0);
        vertices[11].pos = v[0]; vertices[11].tex= glm::vec2(0.0,0.0);   

        //sol
        vertices[12].pos = v[4]; vertices[12].tex= glm::vec2(0.0,1.0);
        vertices[13].pos = v[0]; vertices[13].tex= glm::vec2(1.0,1.0);
        vertices[14].pos = v[3];  vertices[14].tex= glm::vec2(1.0,0.0);
        vertices[15].pos = v[7];  vertices[15].tex= glm::vec2(0.0,0.0);  

        //alt
        vertices[16].pos = v[7];  vertices[16].tex= glm::vec2(0.0,1.0);
        vertices[17].pos = v[6];  vertices[17].tex= glm::vec2(1.0,1.0);
        vertices[18].pos = v[2];  vertices[18].tex= glm::vec2(1.0,0.0);
        vertices[19].pos = v[3];  vertices[19].tex= glm::vec2(0.0,0.0);   
        //arka
        vertices[20].pos = v[4];  vertices[20].tex= glm::vec2(0.0,1.0);
        vertices[21].pos = v[5];  vertices[21].tex= glm::vec2(1.0,1.0);
        vertices[22].pos = v[6];  vertices[22].tex= glm::vec2(1.0,0.0);
        vertices[23].pos = v[7];  vertices[23].tex= glm::vec2(0.0,0.0);   

        for(int i=0;i<faceCount;i++)
        {
            int index= i;
            indices[i*6]   =index*4; indices[i*6+1] =index*4+1; indices[i*6+2] =index*4+2;
            indices[i*6+3] =index*4; indices[i*6+4] =index*4+2; indices[i*6+5] =index*4+3;
        }
        vao = createTextureBuffers(vertices,indices);
        vaoMap["cube"] = vao;            
        vao.primitiveType = GL_TRIANGLES;   
    }
    else
    {
        vao = vaoMap["cube"];
    }
    Mesh3D *mesh= new Mesh3D();
    mesh->name = "cube";
    mesh->parent=0;
    mesh->vertexArrayObject = vao;

    return mesh;
}
Mesh3D* MeshManager::createGrid() 
{
    VertexArrayObject vao;

    if(!vaoMap.count("grid"))
    { 
        unsigned int vertexArrayObjectId;
        
        float length = 10;
        int hVertexCount = length*4+1;
        int vVertexCount = length*4+1;

        int vertexCount = vVertexCount*hVertexCount;
        float distance= length/hVertexCount;

        VertexList vertices;
 
        IndexList   indices;    

        for(int i=0;i<hVertexCount*2+1;i++)
        {
            float x1 = -length;
            float y1 = 0.0f;
            float z1 = -length+i*distance;

            float x2 = length;
            float y2 = 0.0f;
            float z2 = -length+i*distance;
            vertices.emplace_back(x1,y1,z1);
            vertices.emplace_back(x2,y2,z2);

            vertices.emplace_back(z1,y1,x1);
            vertices.emplace_back(z2,y2,x2);   

            indices.push_back(i*4);
            indices.push_back(i*4+1);
            indices.push_back(i*4+2);
            indices.push_back(i*4+3);            
        

        }
        
        vao = createBuffers(vertices,indices);
        vaoMap["grid"] = vao;  
        vao.primitiveType = GL_LINES;     
          
    }
    else
    {
        vao = vaoMap["grid"];
    }
    Mesh3D *mesh= new Mesh3D;
    mesh->name="Grid";
    mesh->parent= 0;
    mesh->vertexArrayObject = vao;

    return mesh;        
}
VertexArrayObject MeshManager::createBuffers(VertexList& vertices,IndexList& indices)
{
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    unsigned int indexBufferId;

    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(glm::vec3),0);
    glEnableVertexAttribArray(0);  

    VertexArrayObject vao;
    vao.indexCount = indices.size();
    vao.id= vertexArrayObjectId;
    return vao;
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