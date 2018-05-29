#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 UV;
//片元所在世界位置
out vec3 fragPosition;
out vec3 fragNormal;

uniform mat4 mvp;
uniform mat4 m;

void main()
{
	UV = aUV;
	fragNormal = aNormal;
	fragPosition = vec3( m * vec4(aPosition,1.0f) );
	gl_Position = mvp * vec4(aPosition, 1.0);
}