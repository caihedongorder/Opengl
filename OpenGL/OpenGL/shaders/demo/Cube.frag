#version 330 core
out vec4 fragColor;

in vec2 UV;
in vec4 fragPosition;
in vec3 fragNormal;
in vec4 fragLightColor;
in vec3 fraglightPosition;

uniform sampler2D base;


void main()
{
	float ambient = 0.3;
	fragColor = vec4(1,0,0,1);
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fraglightPosition - vec3(fragPosition));
	float diffuse = max(dot(lightDir,norm),0);
	fragColor = texture(base,UV*1.0f) * (ambient + diffuse)*fragLightColor;
	//fragColor = vec4(vec3(normalize(fraglightPosition)),1.0f);
	//fragColor = mix(fragColor,vec4(0,1,0,1),0.1f);
}