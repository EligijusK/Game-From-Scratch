//
// Created by Eligijus Kiudys on 2021-06-30.
//
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "inc/mesh.h"
#include "util.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "inc/Shader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Mesh::Mesh(char *filename)
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    tinyobj::attrib_t att;
    std::string warn;
    std::string err;
    std::string base_dir = "/";


    bool ret = tinyobj::LoadObj(&att, &shapes, &material, &warn, &err, filename, base_dir.c_str()); // boxUv.obj

    if (ret) {
        //std::cout << att.vertices.size() / 3;
        glGenVertexArrays(1, &m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);
        std::vector<Vertex> meshData;
        std::vector<unsigned int> indices;


        //vec3 positions[numVertecis]; // add one on creation
        int index = 0;
        for(int mesh = shapes.size()-1; mesh >= 0; mesh--) {
            size_t index_offset = 0;
            //std::cout << size_t(shapes[mesh].mesh.num_face_vertices[3]) << std::endl;
            for (int i = 0; i < shapes[mesh].mesh.num_face_vertices.size(); i++) {
                size_t fv = size_t(shapes[mesh].mesh.num_face_vertices[i]);
                //std::cout << "indices " << idx << std::endl;
                for (size_t v = 0; v < fv; v++) {

                    tinyobj::index_t idx = shapes[mesh].mesh.indices[index_offset + v];

                    tinyobj::real_t vx = att.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = att.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = att.vertices[3 * size_t(idx.vertex_index) + 2];

                    //shapes[mesh].mesh
                    tinyobj::real_t tx = att.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = att.texcoords[2 * size_t(idx.texcoord_index) + 1];

                    tinyobj::real_t nx = att.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = att.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = att.normals[3 * size_t(idx.normal_index) + 1];

                    //glm_vec2_copy(tmpUV, textCoords[index]); // zombies could be a problem, try to fix it using vector and convert it to array
                    vec2 uv{tx, ty};
                    vec3 position{vx, vy, vz};
                    vec3 normals {nx,ny,nz};
                    Vertex vertex(position, uv,normals);

                    meshData.push_back(vertex);
                    indices.push_back(indices.size());

                    index++;

                }



                index_offset += fv;
                //std::cout << fv << std::endl;
            }
        }

        positions = new vec3[meshData.size()];
        textCoords = new vec2[meshData.size()];
        normals = new vec3[meshData.size()];
        indicesArray = new unsigned int[meshData.size()];

        for (int i = 0; i < meshData.size(); ++i) {
            glm_vec2_copy(*meshData[i].GetTexCoord(), textCoords[i]);
            glm_vec3_copy(*meshData[i].GetPos(), positions[i]);
            glm_vec3_copy(*meshData[i].GetNormal(), normals[i]);
            indicesArray[i] = indices[i];
        }

        std::cout << index << std::endl; // 2766
        m_drawCount = meshData.size();
        m_verticesCount = meshData.size();
        SendData();
        glBindVertexArray(0);
    }


}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int *indices, int numIndices)
{

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    positions = new vec3[numVertices];
    textCoords = new vec2[numVertices];
    normals = new vec3[numVertices];
    indicesArray = new unsigned int[numIndices];

    for(int i = 0; i < numVertices; i++)
    {
        glm_vec3_copy(*vertices[i].GetPos(), positions[i]);
        glm_vec3_copy(*vertices[i].GetTexCoord(), textCoords[i]);
        //glm_vec3_copy(*vertices[i].GetNormal(), normals[i]);
    }

    std::copy(indices, indices+numIndices, indicesArray);

    m_drawCount = numIndices;
    m_verticesCount = numVertices;


//    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
//    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (positions[0]), positions, GL_STATIC_DRAW);
//
//
//
//    char posName[] = "vPos";
//    GLuint vPos = Shader::get_shader_index(posName);
//    glEnableVertexAttribArray(vPos);
//    glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, sizeof(positions[0]), (void*) 0);
//
//
//    // text coords;
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
//    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (textCoords[0]), textCoords, GL_STATIC_DRAW);
//    //std::cout << m_vertexArrayBuffers[POSITION_VB];
//
//    int textCoorsIndex = Shader::get_shader_index("textCoord");
////    std::cout << textCoorsIndex << std::endl;
////    std::cout << textCoorsIndex << std::endl;
//    glEnableVertexAttribArray(textCoorsIndex);
//    glVertexAttribPointer(textCoorsIndex, 2, GL_FLOAT, GL_FALSE, sizeof(textCoords[0]), (void*) 0);
//
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof (indices[0]), indices, GL_STATIC_DRAW);
//    glBindVertexArray(0);

}

Mesh::~Mesh()
{

    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{

    SendData();

    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::SendData()
{

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,  m_verticesCount * sizeof (positions[0]), positions, GL_STATIC_DRAW);

    char posName[] = "vPos";
    vPos = Shader::get_shader_index(posName);
    glEnableVertexAttribArray(vPos);
    int vecSizeVertPosition = 3; // this can't pass over 4 cause it pass vector value
    glVertexAttribPointer(vPos, vecSizeVertPosition, GL_FLOAT, GL_FALSE, sizeof(positions[0]), (void*) 0);

    // text coords;

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_verticesCount * sizeof (textCoords[0]), textCoords, GL_STATIC_DRAW);

    textCoorsIndex = Shader::get_shader_index("textCoord");
    glEnableVertexAttribArray(textCoorsIndex);
    glVertexAttribPointer(textCoorsIndex, 2, GL_FLOAT, GL_FALSE, sizeof(textCoords[0]), (void*) 0);

    //normals

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER,  m_verticesCount * sizeof (normals[0]), normals, GL_STATIC_DRAW);


    char normal[] = "vNorm";
    vNorm = Shader::get_shader_index(normal);
    glEnableVertexAttribArray(vNorm);
    int vecSizeVertNormal = 3; // this can't pass over 4 cause it pass vector value
    glVertexAttribPointer(vNorm, vecSizeVertNormal, GL_FLOAT, GL_FALSE, sizeof(normals[0]), (void*) 0);


    // indices

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_drawCount * sizeof (indicesArray[0]), indicesArray, GL_STATIC_DRAW);

}