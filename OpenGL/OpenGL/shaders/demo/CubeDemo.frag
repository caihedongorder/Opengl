#version 330 core
out vec4 fragColor;

in vec2 UV;
uniform sampler2D base;

void main()
{
	fragColor = vec4(1,0,0,1);
}