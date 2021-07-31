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

class GameObject {

public:
    GameObject(Transform *transform, Shader *shader, Texture *texture, Mesh *mesh, Camera *camera);
    void Update();
    Transform *transform;
    Shader *shader;
    Texture *texture;
    Mesh *mesh;
    Camera *camera;

private:

};


#endif //GAME_FROM_SCRACH_GAMEOBJECT_H
