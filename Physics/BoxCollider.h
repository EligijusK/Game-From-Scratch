//
// Created by Eligijus Kiudys on 2021-07-10.
//

#ifndef GAME_FROM_SCRACH_BOXCOLLIDER_H
#define GAME_FROM_SCRACH_BOXCOLLIDER_H
#include <cglm/cglm.h>
#include <vector>

class BoxCollider {
public:
    BoxCollider(vec3 &position, vec3 &size) {
        glm_vec3_copy(position, this->position);
        glm_vec3_copy(size, this->size);

        boxCorners[0] = new float[3] {position[0] - size[0]/2, position[1] - size[1]/2, position[3]};
        boxCorners[1] = new float[3] {position[0] - size[0]/2, position[1] + size[1]/2, position[3]};
        boxCorners[2] = new float[3] {position[0] + size[0]/2, position[1] - size[1]/2, position[3]};
        boxCorners[3] = new float[3] {position[0] + size[0]/2, position[1] + size[1]/2, position[3]};

        boxCorners[0] = new float[3] {position[0] - size[0]/2, position[1] - size[1]/2, position[3]};
        boxCorners[1] = new float[3] {position[0] - size[0]/2, position[1] + size[1]/2, position[3]};
        boxCorners[2] = new float[3] {position[0] + size[0]/2, position[1] - size[1]/2, position[3]};
        boxCorners[3] = new float[3] {position[0] + size[0]/2, position[1] + size[1]/2, position[3]};

    }

    bool IntersectCollision(BoxCollider boxCollider);

    vec3 &GetPositon();
    vec3 &GetSize();

private:
    float *boxCorners[4];
    vec3 position;
    vec3 rotation;
    vec3 size;
};


#endif //GAME_FROM_SCRACH_BOXCOLLIDER_H
