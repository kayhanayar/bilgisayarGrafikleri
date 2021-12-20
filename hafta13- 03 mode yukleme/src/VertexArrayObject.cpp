#include "VertexArrayObject.hpp"
#include<glad/glad.h>
VertexArrayObject::VertexArrayObject()
{
    id=0;
}
void VertexArrayObject::use()
{
    glBindVertexArray(id);
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 
    glEnableVertexAttribArray(1); 
}
void VertexArrayObject::draw()
{
    glDrawElements(primitiveType,indexCount,GL_UNSIGNED_INT,0);
}
void VertexArrayObject::unuse()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);  
    glDisableVertexAttribArray(1); 
    glDisableVertexAttribArray(2); 
}