#shader vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_Model;

uniform mat4 u_VP;

void main()
{
	gl_Position = u_VP * u_Model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}


#shader fragment

#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	float gamma = 2.2;
	FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.95);
	FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}