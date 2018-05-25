#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aUV;

uniform mat4 mvp;

out vec2 OutUV;

void main()
{
	gl_Position = mvp * vec4(aPosition,1.0f);
	OutUV = aUV;
}