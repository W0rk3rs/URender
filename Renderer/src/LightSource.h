#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

#include "GlfW/glfw3.h"

namespace light {

	struct SourceCara {
		glm::vec3 SourcePos;
		glm::vec3 SourceAmbient;
		glm::vec3 SourceDiffuse;
		glm::vec3 SourceSpecular;
	};


	class LightSource
	{
	public:
		LightSource(std::shared_ptr<VertexBuffer> VBO);
		~LightSource();

		void OnRender(const glm::mat4& vp);
		void OnImGuiRender();

		glm::vec3 GetLightPos();
		glm::vec3 GetLightDiffuse();
		glm::vec3 GetLightAmbient();
		glm::vec3 GetLightSpecular();

		void SetLightCara(glm::vec3 Pos, glm::vec3 Diffuse, glm::vec3 Specular);

		void SetVP(const glm::mat4& vp);

	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::vector<std::unique_ptr<Texture>> texture;


		float Scale;

		SourceCara m_SourceCara;

		GLFWwindow* m_Window;
	};
}