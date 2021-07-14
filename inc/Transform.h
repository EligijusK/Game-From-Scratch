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

    inline mat4 * getModel()
    {
        glm_mat4_identity(resMatrix);
        mat4 rotMatrix;
        mat4 rotX;
        glm_mat4_identity(rotX);
        mat4 rotY;
        glm_mat4_identity(rotY);
        mat4 rotZ;
        glm_mat4_identity(rotZ);
        glm_rotate(rotX, glm_rad(m_rot[0]), vec3{1,0,0});
//        glm_rotate(rotY, glm_rad(m_rot[1]), vec3{0,1,0});
//        glm_rotate(rotZ, glm_rad(m_rot[2]), vec3{0,0,1});
        glm_mat4_mulN((mat4 *[]){ &rotX, &rotY, &rotZ}, 3, rotMatrix);

        mat4 scaleMatrix;
        glm_mat4_identity(scaleMatrix);
        glm_scale(scaleMatrix, m_scale);


        mat4 translateMatrix;
        glm_mat4_identity(translateMatrix);
        glm_translate(translateMatrix, m_pos);

//        vec3 invPos;
//        glm_vec3_negate_to(m_pos, invPos);
//        glm_translate(poseMatrix, invPos);


//        glm_mat4_mul(poseMatrix, rotMat, resMatrix);
        //glm_mat4_mul(poseMatrix, scaleMatrix, resMatrix);

        glm_mat4_mulN((mat4 *[]){&translateMatrix, &scaleMatrix, &rotMatrix}, 3, resMatrix);

/* if you don't want to use mulN, same as above */
//        glm_mat4_mul(transform3, transform2, finalTransform);
//        glm_mat4_mul(finalTransform, transform1, finalTransform);
        //glm_mat4_copy(poseMatrix, resMatrix);

        return &resMatrix;
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
    mat4 resMatrix;
};

#endif