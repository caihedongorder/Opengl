#version 330 core
out vec4 fragColor;

in vec2 UV;
in vec4 fragPosition;
in vec3 fragNormal;

uniform sampler2D base;
uniform vec4 lightColor;
uniform vec3 lightPosition;


void main()
{
	float ambient = 0.3;
	fragColor = vec4(1,0,0,1);
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(lightPosition - vec3(fragPosition));
	float diffuse = max(dot(lightDir,norm),0);

	fragColor = texture(base,UV*1.0f) * (ambient + diffuse)*lightColor;
}