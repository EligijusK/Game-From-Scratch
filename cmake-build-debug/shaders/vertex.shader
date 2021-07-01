#version 110
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
attribute vec2 textCoord;

uniform mat4 transform;

varying vec3 color;
varying vec2 textCoord0;
void main()
{
    gl_Position = mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) * vec4(vPos, 1.0, 1.0);
    color = vCol;
    if(MVP[1][3] > 0.0)
    {
        color = vec3(0,1,0);
    }
    else
    {
        color = vec3(1,0,0);
    }

    textCoord0 = textCoord;
}