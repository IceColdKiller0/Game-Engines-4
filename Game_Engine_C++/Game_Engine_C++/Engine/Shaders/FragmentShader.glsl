#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

struct Light
{
	vec3 lightPos;
	float ambValue;
	float diffValue;
	float specValue;
	vec3 lightColour;
};

uniform sampler2D inputTexture;
uniform Light light;
uniform vec3 viewPos;

out vec4 fColour;

void main()
{
	//Ambient
	vec3 ambient = light.ambValue * texture(inputTexture, TexCoords).rgb * light.lightColour;
	
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffValue) * texture(inputTexture, TexCoords).rgb * light.lightColour;
	
	//Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specValue) * light.lightColour;
	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, 1.0f);
	
	//fColour = texture(inputTexture, TexCoords);
}