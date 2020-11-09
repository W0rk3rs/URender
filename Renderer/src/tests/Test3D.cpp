#include "Test3D.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

#include "Renderer.h"


namespace test {

	Test3D::Test3D(GLFWwindow* window)
		:m_Proj(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
		 m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0f))),
		 m_Window(window)
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };

		glEnable(GL_DEPTH_TEST); // Very important for 3D

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 6 * 6 * 5 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);


		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);


		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Shader3D.shader");

		m_Shader->Bind();

		texture.push_back(std::make_unique<Texture>("res/textures/tile1.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/commie.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/KarlMarx.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/smiley.png"));
		texture.push_back(std::make_unique<Texture>("res/textures/matrix.jpg"));

		
		m_Shader->SetUniform1i("Texture1", 0);
		m_Shader->SetUniform1i("Texture2", 1);


		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();

		Camera::InitCamera((GLFWwindow*)m_Window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f, 0.0f);

	}

	Test3D::~Test3D()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Test3D::OnUpdate(float deltaTime)
	{

	}

	void Test3D::OnRender()
	{
		Camera::PollInput();

		m_Proj = glm::perspective(glm::radians(Camera::GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);

		m_View = Camera::GetViewMatrix();

		GLCall(glClearColor(0.5f, 0.5f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;

		m_Shader->Bind();
		texture[0]->Bind(0);
		texture[1]->Bind(1);

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glm::mat4 vp = m_Proj * m_View;

		m_Shader->SetUniformMat4f("u_VP", vp);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, 0.1f *(i+1) * (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.3f));

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_Model", model);
			
			if (i % 4 == 0)
				texture[1]->Bind(1);

			else if(i % 4 == 1)texture[2]->Bind(1);

			else if (i % 4 == 2)texture[3]->Bind(1);

			else if (i % 4 == 3)texture[4]->Bind(1);


			//renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			m_VAO->Bind();
			m_VertexBuffer->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void Test3D::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Press C to control direction with mouse"
			"\nPress N to realease directional control"
			"\nPress M to access menu"
			"\nPress 2 to enter polygon mode"
			"\nPress 1 to return to normal mode"
			"\nPress esc to leave"
			"\nPress W,A,S,D to move the camera"
			"\nScroll up and down to zoom in and out");
	}
}