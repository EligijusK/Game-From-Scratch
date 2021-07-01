//
// Created by Eligijus Kiudys on 2021-06-30.
//

#ifndef GAME_FROM_SCRACH_MESH_H
#define GAME_FROM_SCRACH_MESH_H

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <string>
#include <vector>

struct Vertex
{
public:
    Vertex( vec3& poss,  vec2& texCoords, vec3& normals)
    {
        glm_vec3_copy(poss, pos);
        glm_vec3_copy(texCoords, texCoord);
        glm_vec3_copy(normals, normal);
    }

    vec3* GetPos() { return &pos; }
    vec2* GetTexCoord() { return &texCoord; }
    vec3* GetNormal() { return &normal; }

private:
    vec3 pos;
    vec2 texCoord;
    vec3 normal;
};

enum MeshBufferPositions
{
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    INDEX_VB
};

class Mesh
{
public:
    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices);

    void Draw();

    virtual ~Mesh();
protected:
private:
    static const unsigned int NUM_BUFFERS = 4;
    void operator=(const Mesh& mesh) {}
    Mesh(const Mesh& mesh) {}

    //void InitMesh(const IndexedModel& model);

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif