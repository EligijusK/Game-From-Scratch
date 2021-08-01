//
// Created by Eligijus Kiudys on 2021-07-29.
//

#ifndef GAME_FROM_SCRACH_PHYSICS_H
#define GAME_FROM_SCRACH_PHYSICS_H


#include "SphereCollider.h"
#include "BoxCollider.h"

class Physics {

public:
    void Update();
    bool Intersect(SphereCollider sphereCollider, SphereCollider secSphereCollider);
    bool Intersect(BoxCollider boxCollider, BoxCollider secBoxCollider );
    bool Intersect(SphereCollider sphereCollider, BoxCollider boxCollider);
};


#endif //GAME_FROM_SCRACH_PHYSICS_H
