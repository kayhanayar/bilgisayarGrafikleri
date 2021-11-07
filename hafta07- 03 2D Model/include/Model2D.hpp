#ifndef Model2D_hpp
#define Model2D_hpp


class Model2D
{
public:
    Model2D();

    setBufferIds(unsigned int vaoId,unsigned textureId);
    
    setIndexCount(unsigned int indexCount;)
private:
    unsigned int    indexCount;
    glm::mat3       mtxWorld;
    unsigned int    vertexArrayObjectId;
    unsigned int    textureId;
};


#endif;