#ifdef __APPLE__
    #include "include/GLFW/glfw3.h"
#else
    #include <GL/glew.h>
#endif
#include "inc/camera.h"
#include "inc/Shader.h"
#include "inc/mesh.h"
#include "inc/window.h"
#include "inc/Texture.h"
#include "Physics/SphereCollider.h"
#include "Physics/BoxCollider.h"
#include "inc/GameObject.h"
#include "Physics/Physics.h"

#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>


using namespace std;

#define PI 3.14159265

float Jump(float deltaTime, float h)
{

    float u = 2;
    float jumpAngle = 90;
    float y = ((u*jumpAngle*PI/180)*deltaTime) + (0.5*(-9.8)*pow(deltaTime, 2)) + h;
    //std::cout << "time: " << deltaTime << "distance: " << y << std::endl;
    return y;
}

int main(void)
{

    Physics physics;
    Window window(640, 480);

    vec3 cameraPosition{0.f, 0.f, -4.f};
    vec3 cameraAngle{0, 0,0};
    Camera camera(cameraPosition, cameraAngle, 70.f,  640/480, 0.1f, 1000.f);

    vec3 objectPosition{0.f, 0.f, 0.f};
    vec3 rotation{ 0, 0, 0};
    vec3 scale {1, 1, 1};

    vec3 size {1, 1, 0};
    Transform transformCollider(objectPosition,rotation,scale);
    BoxCollider collider(&transformCollider, size);

    vec3 positionForCollider {0,0,0};
    Transform secTransformCollider(positionForCollider,rotation,scale);
    BoxCollider secCollider(&secTransformCollider, size);

    std::cout << physics.Intersect(collider, secCollider) << std::endl;

    float **verts = collider.GetBoxCorners();

    vec3 ve1[]{
            {verts[0][0], verts[0][1], 0.0f}, // top right point
            {verts[1][0], verts[1][1], 0.0f}, // top left point
            {verts[2][0], verts[2][1], 0.0f}, // bottom left point
            {verts[3][0], verts[3][1], 0.0f}, // bottom right point
    };


    float **verts2 = secCollider.GetBoxCorners();

    vec3 ve2[]{
            {verts2[0][0], verts2[0][1], 0.0f}, // top right point
            {verts2[1][0], verts2[1][1], 0.0f}, // top left point
            {verts2[2][0], verts2[2][1], 0.0f}, // bottom left point
            {verts2[3][0], verts2[3][1], 0.0f}, // bottom right point
    };


    //     -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
    //     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    //    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left

    vec2 tex[]{
            {0,0},
            {1,0},
            {1,1},
            {1,1},
            {0,1},
            {0,0}


    };

    vec3 nor[]{
            {0,0,0},
            {0,0,0},
            {0,0,0},
            {0,0,0},
            {0,0,0},
            {0,0,0}
    };


    Vertex vert1[] {Vertex(ve1[0], tex[0], nor[0]),
                    Vertex(ve1[1], tex[1], nor[1]),
                    Vertex(ve1[2], tex[2], nor[2]),
                    Vertex(ve1[3], tex[3], nor[3]),
                };

    Vertex vert2[] {Vertex(ve2[0], tex[0], nor[0]),
                    Vertex(ve2[1], tex[1], nor[1]),
                    Vertex(ve2[2], tex[2], nor[2]),
                    Vertex(ve2[3], tex[3], nor[3]),
    };

    Shader shader("shaders/vertex.shader","shaders/fragment.shader");

    // mesh must be after shader because of singleton
    unsigned int ind[] {0,1,2, 1, 3, 2};
    //std::cout << sizeof(vert)/sizeof(vert[0]) << std::endl;
    Mesh mesh(vert1, sizeof(vert1)/sizeof(vert1[0]), ind, sizeof(ind)/sizeof(ind[0]));

    Mesh mesh2(vert2, sizeof(vert2)/sizeof(vert2[0]), ind, sizeof(ind)/sizeof(ind[0]));

    Mesh meshObj("boxUv.obj");

    Texture texture("textures/bricks.png");

    Transform transform(objectPosition, rotation, scale);

    SphereCollider sphereCollider(&transform, 1);

    vec3 secObjectPosition{1.51f, 0.f, 0.f};
    Transform secTransform(secObjectPosition, rotation, scale);
    SphereCollider secSphereCollider(&secTransform, 1);

    GameObject go(&transform, &shader, &texture, &mesh, &camera);
    GameObject goSec(&secTransform, &shader, &texture, &mesh2, &camera);


    std::cout << "sphere with box: " << physics.Intersect(secSphereCollider, collider) << std::endl;

    GameObject goObj(&transform, &shader, &texture, &meshObj, &camera);

    cout << "x: " << objectPosition[0] << endl;
    go.CreateCircleMesh(1, 100);
    //goSec.CreateCircleMesh(1, 100);
    float counter = 0.f;

    clock_t begin_time = clock();
    float h = *go.transform->getPos()[1];



    while (window.run())
    {
        //float diffticks = clock() - begin_time;
        //double deltaTime=(diffticks)/(CLOCKS_PER_SEC/10);
        window.clear_viewport();
//        if(true) {
//            float y = Jump(deltaTime, h);
//            vec3 position{*go.transform->getPos()[0], y, *go.transform->getPos()[2]};
//            go.transform->setPos(position);
//        }
        //goObj.Update();
        go.Update();
        goSec.Update();


        window.swap_buffer();


    }

    window.destroy_window();
    exit(EXIT_SUCCESS);
}

