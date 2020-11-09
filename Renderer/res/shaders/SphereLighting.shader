#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out mat4 m_View;
out mat3 TBN;

uniform vec3 u_LightPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform mat4 u_VP;

void main()
{
	vec3 T = normalize(vec3((u_View * u_Model) * vec4(aTangent, 0.0)));
	vec3 N = normalize(vec3((u_View * u_Model) * vec4(aNormal, 0.0)));
	vec3 B = normalize(cross(N, T));

	TBN = mat3(T, B, N);

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
uniform sampler2D normalMap;


struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirLight dirLight;
uniform Material material;
uniform PointLight light;

out vec4 FragColor;

in mat4 m_View;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBN;


void main()
{
	vec3 norm = texture(normalMap, TexCoords).rgb;
	//norm = norm * 2.0 - 1.0;
	norm = normalize(TBN * norm);


	vec3 LightPos;
	LightPos = vec3(m_View * vec4(light.position, 1.0));
	vec3 lightDistance = LightPos - FragPos;

	float distance = length(lightDistance);
	float attenuation = 1.0 / distance;

	vec3 ambient = light.ambient *vec3(texture(materialDiffuse, TexCoords));
	ambient *= attenuation;
	

	//vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightDistance);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(materialDiffuse, TexCoords));
	diffuse *= attenuation;

	vec3 viewDir = normalize(-FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
	vec3 specular =  light.specular * spec * (vec3(1.0f) - vec3(texture(materialSpecular, TexCoords)));
	specular *= attenuation;

	vec3 emission = vec3(0.0f);
	
	vec3 result = ambient + diffuse + specular + emission;

	float gamma = 2.2;
	result = pow(result, vec3(1.0/gamma));
	FragColor = vec4(result, 1.0);

}