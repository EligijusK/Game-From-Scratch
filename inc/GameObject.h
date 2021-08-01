//
// Created by Eligijus Kiudys on 2021-07-29.
//

#ifndef GAME_FROM_SCRACH_GAMEOBJECT_H
#define GAME_FROM_SCRACH_GAMEOBJECT_H
#include "Mesh.h";
#include "Camera.h";
#include "Transform.h";
#include "Shader.h";
#include "Texture.h";
#include "../Physics/BoxCollider.h"
#include "../Physics/SphereCollider.h"

class GameObject {

public:
    GameObject(Transform *transform, Shader *shader, Texture *texture, Mesh *mesh, Camera *camera);
    void Update();
    void CreateCircleMesh(float radius, int numberOfSides);
    Transform *transform;
    Shader *shader;
    Texture *texture;
    Mesh *mesh;
    Camera *camera;
    BoxCollider *boxCcollider;
    SphereCollider *sphereCollider;

private:

};


#endif //GAME_FROM_SCRACH_GAMEOBJECT_H
