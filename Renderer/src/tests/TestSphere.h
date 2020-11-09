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

	class TestSphere : public Test
	{
	public:
		TestSphere(GLFWwindow* window);
		~TestSphere();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::vector<std::unique_ptr<Texture>> texture;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		static Camera m_Camera;
		std::vector<std::unique_ptr<light::LightSource>> light;

		int m_Layers;
		float m_Radius;

		int CacheLayers;
		int m_CacheCounter = 0;
		//float CacheRadius;

		int m_TrianglesNumber;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

		GLFWwindow* m_Window;
		
		void MakeSphereVertices();
	};

}

