#version 330 core
out vec4 fragColor;
in vec2 OutUV;

uniform sampler2D base;

void main()
{
	fragColor = texture(base,OutUV);
}