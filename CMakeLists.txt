cmake_minimum_required(VERSION 3.19)
project(Game_From_Scrach)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
find_package(glfw3 REQUIRED)

set(INC_DIR ${Game_From_Scrach_SOURCE_DIR}/include)
set(LINK_DIR ${Game_From_Scrach_SOURCE_DIR}/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(Game_From_Scrach main.cpp inc/Shader.h shader.cpp inc/camera.h inc/mesh.h mesh.cpp inc/mesh.h inc/window.h window.cpp include/stb_image.h include/stb_image_write.h Texture.cpp inc/Texture.h inc/Transform.h include/tiny_obj_loader.h Physics/BoxCollider.cpp Physics/BoxCollider.h Physics/SphereCollider.cpp Physics/SphereCollider.h)

target_link_libraries (Game_From_Scrach glfw3)


 