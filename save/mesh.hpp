#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.hpp"

struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec3 tangent, const glm::vec3 Bitangent)
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
        this->tangent = tangent;
        this->Bitangent = Bitangent;
    }
    
    glm::vec3* GetPos() { return &pos; }
    glm::vec2* GetTexCoord() { return &texCoord; }
    glm::vec3* GetNormal() { return &normal; }
    glm::vec3* GetTangent(){return &tangent;}
    glm::vec3* GetBitangent(){return &Bitangent;}
    
private: //Attributes for our Vec, should be private
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
    glm::vec3 Bitangent;
    glm::vec3 tangent;
};

struct Texture{
    unsigned int tID;
    std::string type;
    std::string path;
};

enum MeshBufferPositions
{
    POSITION_VB, //0
    TEXCOORD_VB, //1
    NORMAL_VB, //2
    INDEX_VB //3
};

class Mesh
{
public:
    void Setup();
    
    void InitMesh(const IndexedModel & model);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& File);
    
    void Draw();
    
    virtual ~Mesh();
protected:
private:
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}
    Mesh(const Mesh& mesh) {}

    GLuint VAO;//vertex array obj
    GLuint VBO[NUM_BUFFERS];
    GLuint EBO;
    unsigned int m_numIndices;
};

#endif
