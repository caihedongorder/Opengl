#version 330 core
out vec4 fragColor;

in vec2 UV;
in vec3 fragPosition;
in vec3 fragNormal;

uniform sampler2D base;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;


void main()
{
	float ambient = 0.3;
	fragColor = vec4(1,0,0,1);
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(lightPosition - fragPosition);

	//diffuse
	float diffuse = max(dot(lightDir,norm),0);

	//ธ฿นโ
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);

	fragColor = texture(base,UV*1.0f) * (ambient + diffuse + spec * specularStrength )*lightColor;
	//fragColor =  mix(fragColor,vec4(vec3(reflectDir),1.0),0.5);
}