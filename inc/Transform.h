//
// Created by Eligijus Kiudys on 2021-07-01.
//

#ifndef GAME_FROM_SCRACH_TRANSFORM_H
#define GAME_FROM_SCRACH_TRANSFORM_H

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "camera.h"
#include "cglm/affine.h"
#include "iostream"

class Transform
{
public:
    Transform(vec3 &pos, vec3 &rot, vec3 &scale)
    {
        glm_vec3_copy(pos, m_pos);
        glm_vec3_copy(rot, m_rot);
        glm_vec3_copy(scale, m_scale);
    }

    inline mat4 & getModel()
    {
        mat4 posMatrix;
        glm_mat4_identity(posMatrix);
        glm_translate(posMatrix, m_pos);
        glm_mat4_transpose(posMatrix);

        mat4 scaleMatrix {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
        glm_scale(scaleMatrix, m_scale);
        std::cout << scaleMatrix[0][0] << std::endl;




        mat4 rotX {{1,0,0,0},
                   {0,1,0,0},
                   {0,0,1,0},
                   {0,0,0,1}};
        glm_rotate(rotX, m_rot[0], vec3{1.0, 0.0, 0.0});
        mat4 rotY {{1,0,0,0},
                   {0,1,0,0},
                   {0,0,1,0},
                   {0,0,0,1}};
        glm_rotate(rotY, m_rot[1], vec3{0.0, 1.0, 0.0});

        mat4 rotZ {{1,0,0,0},
                   {0,1,0,0},
                   {0,0,1,0},
                   {0,0,0,1}};
        glm_rotate(rotZ, m_rot[2], vec3{0.0, 0.0, 1.0});
        mat4 rotMat {{1,0,0,0},
                     {0,1,0,0},
                     {0,0,1,0},
                     {0,0,0,1}};


        glm_mul(rotX, rotY, rotMat);
        glm_mul(rotMat, rotZ, rotMat);

        mat4 resMatrix {{1,0,0,0},
                        {0,1,0,0},
                        {0,0,1,0},
                        {0,0,0,1}};
        mat4 tempResMatrix {{1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {0,0,0,1}};
        glm_mul(posMatrix, rotMat, tempResMatrix);
        glm_mul(tempResMatrix, scaleMatrix, resMatrix);

        return posMatrix;
    }

//    inline glm::mat4 GetMVP(const Camera& camera) const
//    {
//        glm::mat4 VP = camera.GetViewProjection();
//        glm::mat4 M = GetModel();
//
//        return VP * M;//camera.GetViewProjection() * GetModel();
//    }

    inline vec3 *getPos() {return &m_pos;}
    inline vec3 *getRot() {return &m_rot;}
    inline vec3 *getScale() {return &m_scale;}

    inline void setPos(vec3 &pos) { glm_vec3_copy(pos, m_pos);}
    inline void setRot(vec3 &rot) {glm_vec3_copy(rot, m_rot);}
    inline void setScale(vec3 &scale) {glm_vec3_copy(scale, m_scale);}
private:
    vec3 m_pos;
    vec3 m_rot;
    vec3 m_scale;
};

#endif