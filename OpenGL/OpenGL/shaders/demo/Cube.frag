#version 330 core

out vec4 fragColor;

in vec2 UV;
in vec3 fragPosition;
in vec3 fragNormal;

uniform sampler2D base;
uniform vec3 viewPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
uniform Material material;
uniform Light light;

uniform float uvRepeatCount;


void main()
{
	vec3 ambient = vec3(0.3) * material.ambient * light.ambient;
	fragColor = vec4(1,0,0,1);
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(light.position - fragPosition);

	//diffuse
	vec3 diffuse = vec3( max(dot(lightDir,norm),0) ) * material.diffuse * light.diffuse;

	//ธ฿นโ
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 SpecColor = vec3(spec) * material.specular * light.specular;

	fragColor = texture(base,UV*uvRepeatCount) * vec4( ambient + diffuse + SpecColor * specularStrength ,1.0) ;
}