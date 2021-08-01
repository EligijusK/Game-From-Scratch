//
// Created by Eligijus Kiudys on 2021-07-10.
//

#include "SphereCollider.h"


vec3 &SphereCollider::GetPositon()
{
    return *transform->getPos();
}

float SphereCollider::GetRadius()
{
    return radius;
}
