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

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{

    m_drawCount = numVertices;
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    vec3 positions[numVertices+1]; // add one on creation
    vec2 textCoords[numVertices+1];

    for(int i = 0; i < numVertices; i++)
    {
        glm_vec3_copy(*vertices[i].GetPos(), positions[i]);
        glm_vec3_copy(*vertices[i].GetTexCoord(), textCoords[i]);
    }

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    // vPos;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (positions[0]), positions, GL_STATIC_DRAW);



    char posName[] = "vPos";
    GLuint vPos = Shader::get_shader_index(posName);
    glEnableVertexAttribArray(vPos);
    glVertexAttribPointer(vPos, m_drawCount, GL_FLOAT, GL_FALSE, sizeof(positions[0]), (void*) 0);



    // text coords;

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (textCoords[0]), textCoords, GL_STATIC_DRAW);
    std::cout << m_vertexArrayBuffers[POSITION_VB];

    int textCoorsIndex = Shader::get_shader_index("textCoord");
    std::cout << textCoorsIndex << std::endl;
    glEnableVertexAttribArray(textCoorsIndex);
    glVertexAttribPointer(textCoorsIndex, 2, GL_FLOAT, GL_FALSE, sizeof(textCoords[0]), (void*) 0);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);
    //glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_QUADS, 0, m_drawCount);

    glBindVertexArray(0);
}