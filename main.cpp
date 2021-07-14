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
#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>


using namespace std;

int main(void)
{

    Window window(640, 480);

    vec3 cameraPosition{0.f, 0.f, -6.f};
    vec3 cameraAngle{0, 0,0};
    Camera camera(cameraPosition, cameraAngle, 70.f,  640/480, 0.1f, 1000.f);

    vec3 ve[]{
            {-0.6f, -0.4f, 1},
            {0.6f, -0.4f, 1},
            {0.6f, 0.4f, 1},
            {-0.6f, 0.4f, 1},
    };

    vec2 tex[]{
            {0,0},
            {1,0},
            {1,1},
            {0,1},

    };

    vec3 nor[]{
            {0,0,0},
            {0,0,0},
            {0,0,0},
            {0,0,0}
    };


    Vertex vert[] {Vertex(ve[0], tex[0], nor[0]),
                    Vertex(ve[1], tex[1], nor[1]),
                    Vertex(ve[2], tex[2], nor[2]),
                    Vertex(ve[3], tex[3], nor[3])
                };

    Shader shader("shaders/vertex.shader","shaders/fragment.shader");

    // mesh must be after shader because of singleton
    unsigned int ind[] {0,1,2,3};
    Mesh mesh(vert, sizeof(vert)/sizeof(vert[0]), ind, sizeof(ind)/sizeof(ind[0]));

    Texture texture("textures/bricks.png");

    vec3 objectPosition{0.f, 0.f, 0.f};
    vec3 rotation{ 0, 0, 0};
    vec3 scale {1, 1, 1};

    Transform transform(objectPosition, rotation, scale);


    SphereCollider sphereCollider(objectPosition, 10);

    vec3 secObjectPosition{0.f, 0.f, 0.f};
    SphereCollider secSphereCollider(secObjectPosition, 10);


    vec3 size {1, 1, 0};
    vec3 positionForCollider {1,-1.1,0};
    BoxCollider secCollider(positionForCollider, size);
    BoxCollider collider(objectPosition, size);

    std::cout << secCollider.IntersectCollision(collider) << std::endl;


    mesh.MeshInit();
    float counter = 0.f;
    while (window.run())
    {
        window.clear_viewport();

        float sinCounter = sinf(counter);
        float absSinCounter = abs(sinCounter);
        vec3 rot;
        glm_vec3_copy(*transform.getRot(), rot);
        rot[0] = 30;
        transform.setRot(rot);

        shader.use();
        //shader.update(camera);
        mesh.Draw();
        texture.bind(0);
        shader.update(transform, camera);
        window.swap_buffer();
        counter += 0.01f;

    }

    window.destroy_window();
    exit(EXIT_SUCCESS);
}
