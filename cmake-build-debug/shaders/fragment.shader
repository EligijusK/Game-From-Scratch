#version 110
varying vec3 color;
varying vec2 textCoord0;
varying vec3 normal0;
uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse, textCoord0);
//        * clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);
//    gl_FragColor = vec4(color, 1);
}