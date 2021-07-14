
#ifndef GAME_FROM_SCRACH_CAMERA_H
#define GAME_FROM_SCRACH_CAMERA_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

class Camera
{
public:
    Camera(vec3 &pos, vec3 angle, float fov, float aspect, float zNear, float zFar)
    {
        glm_perspective(fov, aspect, zNear, zFar, m_perspective);
        glm_vec3_copy(pos, m_position);
        vec3 forward = {0.f,0.f,1.0f};
        glm_vec3_copy(forward, m_forward);
        glm_vec3_copy(forward, m_forward_temp);
        glm_vec3_copy(angle, m_angle);
        vec3 up = {0.f, 1.f, 0.f};
        glm_vec3_copy(up, m_up);

    }

    mat4 * GetViewProjection()
    {
        //Rotate();
        //std::cout << m_perspective[1][1] << std::endl;
        vec3 added;
        mat4 res;
        glm_mat4_identity(res);
        glm_vec3_add(m_position, m_forward, added);

        glm_lookat(m_position, added , m_up, res );
        glm_mat4_mul(m_perspective, res, result);
        return  &result;
    }


private:
    mat4 m_perspective;
    vec3 m_position;
    vec3 m_angle;
    vec3 m_forward_temp;
    vec3 m_forward;
    vec3 m_up;
    mat4 result;

    void Rotate()
    {

        vec4 kk{m_forward_temp[0], m_forward_temp[1], m_forward_temp[2], 0.0};
        vec4 up{0, 1, 0, 0.0};

        mat4 resAngle;
        glm_mat4_identity(resAngle);
        glm_rotate_x(resAngle, glm_rad(m_angle[0]), resAngle);
        glm_rotate_y(resAngle, glm_rad(m_angle[1]), resAngle);
        glm_rotate_z(resAngle, glm_rad(m_angle[2]), resAngle);


        vec4 multiplyResAngle;
        glm_mat4_mulv(resAngle, kk, multiplyResAngle);
        glm_normalize(multiplyResAngle);

        glm_vec3_copy(multiplyResAngle, m_forward);

        vec4 multiplyAngle;
        glm_mat4_mulv(resAngle, up, multiplyAngle);
        glm_normalize(multiplyAngle);

        glm_vec3_copy(multiplyAngle, m_up); // rotate to the left


    }
};

#endif //GAME_FROM_SCRACH_CAMERA_H
