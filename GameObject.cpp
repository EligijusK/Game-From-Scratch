//
// Created by Eligijus Kiudys on 2021-07-29.
//

#include "inc/GameObject.h"

GameObject::GameObject(Transform *transform, Shader *shader, Texture *texture, Mesh *mesh, Camera *camera)
{
    this->transform = transform;
    this->shader = shader;
    this->texture = texture;
    this->mesh = mesh;
    this->camera = camera;

}

void GameObject::Update() {

//        vec3 rot {0,0,0};
//        glm_vec3_copy(*transform->getRot(), rot);
//        rot[0] = 30;
//        transform->setRot(rot);


        shader->use();
        mesh->Draw();
        texture->bind(0);
        shader->update(*transform, *camera);

}