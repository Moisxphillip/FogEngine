#version 410

in vec2 VertexPosition;
in vec4 VertexColor;
in vec2 VertexUV;

out vec2 FragPos;
out vec4 FragColor;
out vec2 FragUV;

//uniform float Time;


void main()
{
    gl_Position.xy = VertexPosition; //+ vec2(0.2*sin(Time), 0.2*cos(Time));
    gl_Position.z = 0;
    gl_Position.w = 1;
     
    FragPos = VertexPosition;
    FragColor = VertexColor;
    FragUV = vec2(VertexUV.x, 1-VertexUV.y);
}