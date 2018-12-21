#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.hpp"

using namespace std;

struct Vertex //structure to store our object
{
    glm::vec3 pos; //vec3 position (x,y,z)
    glm::vec2 texCoord; // Vec2 texture (p,q)
    glm::vec3 normal; //vec3(x,y,z)
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
    
    void InitMesh();
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    
    void Draw(GLuint shaderID);
    
    virtual ~Mesh();
protected:
private:
    
    vector<Vertex> meshVertices;
    vector<unsigned int> meshIndices;
    vector<Texture> meshTextures;
    
    
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}

    GLuint VAO;//vertex array obj
    GLuint VBO;
    GLuint EBO;
    unsigned int m_numIndices;
};

#endif
