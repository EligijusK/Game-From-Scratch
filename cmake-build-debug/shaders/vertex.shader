#version 110
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec3 vPos;
attribute vec2 textCoord;
attribute vec3 vNorm;

uniform mat4 transform;

varying vec3 color;
varying vec2 textCoord0;
varying vec3 normal0;
void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
    textCoord0 = textCoord;
    normal0 = (MVP * vec4(vNorm, 0.0)).xyz;
}