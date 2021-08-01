//
// Created by Eligijus Kiudys on 2021-07-10.
//

#ifndef GAME_FROM_SCRACH_SPHERECOLLIDER_H
#define GAME_FROM_SCRACH_SPHERECOLLIDER_H
#include <cglm/cglm.h>
#include "../inc/Transform.h"

class SphereCollider {
public:
    SphereCollider(Transform *transform, float radius)
    {
        this->transform = transform;
        this->radius = radius;
    }

    vec3 &GetPositon();
    float GetRadius();

private:
    Transform *transform;
    float radius;
};


#endif //GAME_FROM_SCRACH_SPHERECOLLIDER_H
