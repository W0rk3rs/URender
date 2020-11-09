#pragma once

#include "test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

#include "GlfW/glfw3.h"

namespace test {

	class Test3D : public Test
	{
	public:
		Test3D(GLFWwindow* window);
		~Test3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::vector<std::unique_ptr<Texture>> texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		static Camera m_Camera;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

		GLFWwindow* m_Window;
	};

}

