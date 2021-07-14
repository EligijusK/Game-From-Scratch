//
// Created by Eligijus Kiudys on 2021-07-10.
//

#include <iostream>
#include "BoxCollider.h"

bool BoxCollider::IntersectCollision(BoxCollider boxCollider)
{

    bool colliding = false;
    for (int i = 0; i < 4; ++i) {

        for (int j = 0; j < 4; ++j) {


            vec3 tempOther{boxCollider.boxCorners[i][0], boxCollider.boxCorners[i][1], boxCollider.boxCorners[i][2]};
            vec3 tempLocal{this->boxCorners[j][0], this->boxCorners[j][1], this->boxCorners[j][2]};

            float distanceToOther = glm_vec3_distance(position, tempOther);
            float distanceToLocal = glm_vec3_distance(position, tempLocal);

            if (distanceToOther <= distanceToLocal) {
                colliding = true;
                break;
            }
        }

    }
    return colliding;

}

vec3 &BoxCollider::GetPositon()
{
    return position;
}

vec3 &BoxCollider::GetSize()
{
    return size;
}
