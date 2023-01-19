#version 410 
//in vec2 FragPos;
//in vec4 FragColor;
in vec2 FragUV;

out vec4 GColor;

uniform float Time;
uniform sampler2D SpriteSampler;

void main()
{
    vec4  TextuColor = texture(SpriteSampler, FragUV);
    GColor = TextuColor * vec4((1.0)* sin(Time),
        (1.0)* sin(Time + radians(120)),
        (1.0)* sin(Time + radians(240)), 0);
}