//
// Created by Eligijus Kiudys on 2021-07-10.
//

#ifndef GAME_FROM_SCRACH_BOXCOLLIDER_H
#define GAME_FROM_SCRACH_BOXCOLLIDER_H
#include <cglm/cglm.h>
#include <vector>
#include "../inc/Transform.h"
class BoxCollider {
public:
    BoxCollider(Transform *transfrom, vec3 &size) {
        this->transform = transfrom;
        glm_vec3_copy(size, this->size);
        cornerCount = 4;
        boxCorners = new float *[cornerCount];

        vec3 position {0,0,0};
        glm_vec3_copy(*transform->getPos(), position);

        boxCorners[0] = new float[3] {position[0] - size[0]/2, position[1] - size[1]/2, position[2]};
        boxCorners[1] = new float[3] {position[0] - size[0]/2, position[1] + size[1]/2, position[2]}; // top
        boxCorners[2] = new float[3] {position[0] + size[0]/2, position[1] - size[1]/2, position[2]};
        boxCorners[3] = new float[3] {position[0] + size[0]/2, position[1] + size[1]/2, position[2]}; // top

    }

    vec3 &GetPositon();
    int GetCornerCount();
    vec3 &GetSize();
    float **GetBoxCorners();

private:
    int cornerCount;
    float **boxCorners;
    Transform *transform;
    vec3 rotation;
    vec3 size;
};


#endif //GAME_FROM_SCRACH_BOXCOLLIDER_H
