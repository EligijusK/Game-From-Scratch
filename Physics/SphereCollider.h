//
// Created by Eligijus Kiudys on 2021-07-10.
//

#ifndef GAME_FROM_SCRACH_SPHERECOLLIDER_H
#define GAME_FROM_SCRACH_SPHERECOLLIDER_H
#include <cglm/cglm.h>

class SphereCollider {
public:
    SphereCollider(vec3 &position, float radius)
    {
        glm_vec3_copy(position, this->position);
        this->radius = radius;
    }

    bool Intersected(SphereCollider &sphereCollider);
    vec3 &GetPositon();
    float GetRadius();

private:
    vec3 position;
    float radius;
};


#endif //GAME_FROM_SCRACH_SPHERECOLLIDER_H
