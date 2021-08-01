//
// Created by Eligijus Kiudys on 2021-07-10.
//

#include <iostream>
#include "BoxCollider.h"


vec3 &BoxCollider::GetPositon()
{
    return *transform->getPos();
}

int BoxCollider::GetCornerCount()
{
    return cornerCount;
}

vec3 &BoxCollider::GetSize()
{
    return size;
}

float **BoxCollider::GetBoxCorners()
{
    vec3 position {0,0,0};
    glm_vec3_copy(*transform->getPos(), position);

    boxCorners[0] = new float[3] {position[0] - size[0]/2, position[1] - size[1]/2, position[2]};
    boxCorners[1] = new float[3] {position[0] - size[0]/2, position[1] + size[1]/2, position[2]};
    boxCorners[2] = new float[3] {position[0] + size[0]/2, position[1] - size[1]/2, position[2]};
    boxCorners[3] = new float[3] {position[0] + size[0]/2, position[1] + size[1]/2, position[2]};

    return boxCorners;
}