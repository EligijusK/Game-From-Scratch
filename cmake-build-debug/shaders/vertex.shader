#version 110
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
attribute vec2 textCoord;
varying vec3 color;
varying vec2 textCoord0;
void main()
{
    gl_Position = vec4(vPos, 1.0, 1.0);
    color = vCol;
    textCoord0 = textCoord;
}