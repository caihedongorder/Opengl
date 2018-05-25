#version 330 core
out vec4 fragColor;
in vec2 OutUV;

uniform sampler2D layer0;
uniform sampler2D layer1;

void main()
{
	vec4 layerColor0 = texture(layer0,OutUV);
	vec4 layerColor1 = texture(layer1,OutUV);
	//layerColor1.rgb = layerColor1.rgb * layerColor1.a;
	fragColor = mix(layerColor0,layerColor1,0.4);
	fragColor = mix(fragColor,vec4(1.0f,0.0f,0.0f,1.0f),0.2);
}