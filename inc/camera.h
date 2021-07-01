
#ifndef GAME_FROM_SCRACH_CAMERA_H
#define GAME_FROM_SCRACH_CAMERA_H

#include "cglm/cglm.h"

class Camera
{
public:
    Camera(vec3 &pos, float fov, float aspect, float zNear, float zFar)
    {
        glm_perspective(fov, aspect, zNear, zFar, m_perspective);
        vec3 tmp = {pos[0], pos[1], pos[2]};
        glm_vec3_copy(tmp, m_position);
        vec3 foward = {0.f,0.f,1.0f};
        glm_vec3_copy(foward, m_forward);
        vec3 up = {0.f, 1.f, 0.f};
        glm_vec3_copy(up, m_up);

    }

    mat4 * GetViewProjection()
    {
        vec3 added;
        mat4 res;
        glm_vec3_add(m_position, m_forward, added);
        glm_lookat(m_position, added , m_up, res );
        mat4 resRet;
        glm_mat4_mul(m_perspective, res, resRet);
        return  &resRet;
    }

private:
    mat4 m_perspective;
    vec3 m_position;
    vec3 m_forward;
    vec3 m_up;
};

#endif //GAME_FROM_SCRACH_CAMERA_H
