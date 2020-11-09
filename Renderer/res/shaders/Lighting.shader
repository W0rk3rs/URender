#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out mat4 m_View;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform mat4 u_VP;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
	FragPos = vec3(u_View * u_Model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(u_View * u_Model))) * aNormal;
	TexCoords = aTexCoords;
	m_View = u_View;
}


#shader fragment

#version 330 core
struct Material {

	float shininess;
};
	
uniform sampler2D materialDiffuse;
uniform sampler2D materialSpecular;
uniform sampler2D materialEmission;


struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};



struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 4

uniform Material material;

uniform PointLight light;

uniform DirLight dirLight;

out vec4 FragColor;

in mat4 m_View;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//functions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 LightPos;
	LightPos = vec3(m_View * vec4(light.position, 1.0));

	vec3 lightDistance = LightPos - FragPos;

	float distance = length(lightDistance);
	float attenuation = 1.0 / distance;

	vec3 ambient = light.ambient * vec3(texture(materialDiffuse, TexCoords));
	ambient *= attenuation;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightDistance);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(materialDiffuse, TexCoords));
	diffuse *= attenuation;

	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  light.specular * spec * vec3(texture(materialSpecular, TexCoords));
	specular *= attenuation;

	vec3 emission = vec3(0.0f);
	if (texture(materialSpecular, TexCoords).r <= 0.05)   /*rough check for blackbox inside spec texture */
	{
		/*apply emission texture */
		emission = texture(materialEmission, TexCoords).rgb;

	}
	
	vec3 result = ambient + diffuse + specular + emission;
	float gamma = 2.2;
	result = pow(result, vec3(1.0 / gamma));
	FragColor = vec4(result, 1.0);
}

/*vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, normal);
	float diff = pow(max(dot(-lightDir, viewDir), 0.0f), material.shininess);

	vec3 ambient = light.ambient  * vec3(texture(materialDiffuse, TexCoords));
	vec3 diffuse = light.diffuse  * diff * vec3(texture(materialDiffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(materialSpecular, TexCoords));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(-fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
		light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient  * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}*/