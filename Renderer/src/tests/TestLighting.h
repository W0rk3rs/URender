#pragma once

#include "test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "LightSource.h"

#include <memory>

#include "GlfW/glfw3.h"

namespace test {

	class TestLighting : public Test
	{
	public:
		TestLighting(GLFWwindow* window);
		~TestLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		std::vector<std::unique_ptr<Texture>> texture;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		static Camera m_Camera;
		std::vector<std::unique_ptr<light::LightSource>> light;


		glm::mat4 m_Proj, m_View;

		GLFWwindow* m_Window;
	};

}

