//
// Created by Eligijus Kiudys on 2021-07-10.
//

#include "SphereCollider.h"

bool SphereCollider::Intersected(SphereCollider &sphereCollider)
{
    float distance = glm_vec3_distance(position, sphereCollider.position);
    return radius > distance && sphereCollider.radius > distance;
}

vec3 &SphereCollider::GetPositon()
{
    return position;
}

float SphereCollider::GetRadius()
{
    return radius;
}