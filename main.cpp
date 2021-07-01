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
#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>


using namespace std;

int main(void)
{

    Window window(640, 480);

    vec3 position{1.f, 1.f, 1.f};
    Camera camera(position, 1.f,  1, 1.f, 1.f);

    vec3 ve[]{
            {-0.6f, -0.4f, 1},
            {0.6f, -0.4f, 1},
            {0.6f, 0.4f, 1},
            {-0.6f, 0.4f, 1}
    };

    vec2 tex[]{
            {0,0},
            {1,0},
            {1,1},
            {0,1}
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
    Mesh mesh(vert, sizeof(vert)/sizeof(vert[0]));

    Texture texture("textures/bricks.png");

    vec3 rotation {0, 0, 0};
    vec3 scale {2, 1, 1};

    Transform transform(position, rotation, scale);

    while (window.run())
    {
        window.clear_viewport();

        shader.use();
        //shader.update(camera);
        mesh.Draw();
        texture.bind(0);
        shader.update(transform);
        window.swap_buffer();

    }

    window.destroy_window();
    exit(EXIT_SUCCESS);
}
