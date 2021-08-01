//
// Created by Eligijus Kiudys on 2021-07-29.
//

#include "Physics.h"

bool IntersectVert(vec3 spherePos, float radius, vec3 verPosition);

void Physics::Update() {


}

bool Physics::Intersect(BoxCollider boxCollider, BoxCollider secBoxCollider )
{


    bool colliding = false;
    for (int i = 0; i < 4; ++i) {

        for (int j = 0; j < 4; ++j) {

            float **thisBoxCorners = boxCollider.GetBoxCorners();
            float **otherBoxCorners = boxCollider.GetBoxCorners();
            vec3 tempOther{otherBoxCorners[i][0], otherBoxCorners[i][1], otherBoxCorners[i][2]};
            vec3 tempLocal{thisBoxCorners[j][0], thisBoxCorners[j][1], thisBoxCorners[j][2]};

            float distanceToOther = glm_vec3_distance(boxCollider.GetPositon(), tempOther);
            float distanceToLocal = glm_vec3_distance(boxCollider.GetPositon(), tempLocal);

            if (distanceToOther <= distanceToLocal) {
                colliding = true;
                break;
            }
        }

    }
    return colliding;

}

bool Physics::Intersect(SphereCollider sphereCollider, SphereCollider secSphereCollider)
{

    float distance = glm_vec3_distance(sphereCollider.GetPositon(), secSphereCollider.GetPositon());
    return sphereCollider.GetRadius()*2 > distance && secSphereCollider.GetRadius()*2 > distance;
}

bool Physics::Intersect(SphereCollider sphereCollider, BoxCollider boxCollider)
{
    float **boxCorners = boxCollider.GetBoxCorners();

    boxCorners[2][1];
    boxCorners[3][1];

    vec3 spherePos {0,0,0};
    glm_vec3_copy(sphereCollider.GetPositon(), spherePos);

    vec3 boxPosition {0,0,0};
    glm_vec3_copy(boxCollider.GetPositon(), boxPosition);


    vec3 boxSize {0,0,0};
    glm_vec3_copy(boxCollider.GetSize(), boxSize);

    float radius = sphereCollider.GetRadius();

    float x = boxSize[0]/2;
    float y = boxSize[1]/2;

    float diagonalX = sqrt(pow(x,2) + pow(radius,2));
    float diagonalY = sqrt(pow(y,2) + pow(radius,2));
    //float diagonalZ = sqrt(pow(y,2) + pow(radius,2));




//    if(boxCorners[2][0] > (spherePos[0]-radius) && boxCorners[0][0] > (spherePos[0]-radius) && boxCorners[2][1] < spherePos[1] && boxCorners[3][1] > spherePos[1])
//    {
//        return true;
//    }
//
//    if(-boxCorners[0][0] > (spherePos[0]-radius) && (spherePos[0]-radius) > -boxCorners[2][0] && boxCorners[0][1] < spherePos[1] && boxCorners[1][1] > spherePos[1])
//    {
//        return true;
//    }
//
//    if(boxCorners[1][1] > (spherePos[1]-radius) && (spherePos[1]-radius) > boxCorners[0][1] && boxCorners[3][0] > spherePos[0] && boxCorners[1][0] < spherePos[0])
//    {
//        return true;
//    }

    float distan = glm_vec3_distance(boxCorners[2], spherePos);
    std::cout << "distance: " << distan << " radius: " << radius << std::endl;
    std::cout << "vertices position: " << abs(boxCorners[3][1]) << " sphere x position: " << abs(spherePos[1]) << std::endl;







    //std::cout << "box: " << boxCorners[2][0] << " sphere: " << (spherePos[0]) << std::endl;



//    if(boxCorners[0][1] < (spherePos[1]+radius) && boxCorners[0][0] < spherePos[0] && boxCorners[2][0] > spherePos[0])
//    {
//        return true;
//    }

    bool cornerCheck = false;
    for (int i = 0; i < boxCollider.GetCornerCount(); ++i) {
        cornerCheck = IntersectVert(spherePos, radius, boxCorners[i]);
        if(cornerCheck)
        {
            break;
        }
    }

//    float distance = glm_vec3_distance(*transform->getPos(), *sphereCollider.transform->getPos());
//    bool gg = radius*2 > distance && sphereCollider.radius*2 > distance;

    return cornerCheck;
}

bool IntersectVert(vec3 spherePos, float radius, vec3 verPosition)
{
    if(abs(verPosition[1]) < abs(spherePos[1]) && abs(verPosition[1]) >= abs(spherePos[1])-radius)
    {
        return true;
    }
    if(abs(verPosition[0]) < abs(spherePos[0]) && abs(verPosition[0]) >= abs(spherePos[0])-radius)
    {
        return true;
    } // jei daugiau

    if(abs(verPosition[0]) >= abs(spherePos[0]) && abs(verPosition[1]) >= abs(spherePos[1])-radius)
    {
        return true;
    }

    if(abs(verPosition[1]) >= abs(spherePos[1]) && abs(verPosition[0]) >= abs(spherePos[0])-radius)
    {
        return true;
    } // jei maziau

    return false;
}