#include "TestLighting.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

#include "Renderer.h"

namespace test {

	TestLighting::TestLighting(GLFWwindow* window)
		:m_Proj(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
		 m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0f))),
		 m_Window(window)
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		//unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };

		glEnable(GL_DEPTH_TEST); // Very important for 3D

		m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, 6 * 6 * 8 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);


		//m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_shared<Shader>("res/shaders/Lighting.shader");

		m_Shader->Bind();
		
		texture.push_back(std::make_unique<Texture>("res/textures/container2.png"));
		texture.push_back(std::make_unique<Texture>("res/textures/container2_specular.png"));
		texture.push_back(std::make_unique<Texture>("res/textures/matrix.jpg"));



		m_Shader->SetUniform1i("materialDiffuse", 0);
		m_Shader->SetUniform1i("materialSpecular", 1);
		m_Shader->SetUniform1i("materialEmission", 2);



		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();

		Camera::InitCamera((GLFWwindow*)m_Window, glm::vec3(0.0f, 0.4f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f, 0.0f);

		light.push_back(std::make_unique<light::LightSource>(m_VertexBuffer));
		light[0]->SetLightCara(glm::vec3(1.0f, 1.0f, 1.3f), 
							   glm::vec3(0.5, 0.0, 1.0f), glm::vec3(1.0f));
	}

	TestLighting::~TestLighting()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void TestLighting::OnUpdate(float deltaTime)
	{

	}

	void TestLighting::OnRender()
	{
		Camera::PollInput();

		m_Proj = glm::perspective(glm::radians(Camera::GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);

		m_View = Camera::GetViewMatrix();

		GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//Renderer renderer;

		m_Shader->Bind();
		texture[0]->Bind(0);
		texture[1]->Bind(1);
		texture[2]->Bind(2);


		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(-5.0f, 1.0f, 0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		m_Shader->SetUniformMat4f("u_View", m_View);

		m_Shader->SetUniformMat4f("u_Proj", m_Proj);
		
		glm::vec3 lightPos = light[0]->GetLightPos();
		m_Shader->SetUniformVec3fv("light.position", lightPos);	

		glm::vec3 lightAmbient = light[0]->GetLightAmbient();
		m_Shader->SetUniformVec3fv("light.ambient", lightAmbient);
		
		glm::vec3 lightDiffuse = light[0]->GetLightDiffuse();
		m_Shader->SetUniformVec3fv("light.diffuse", lightDiffuse);

		glm::vec3 lightSpecular = light[0]->GetLightSpecular();
		m_Shader->SetUniformVec3fv("light.specular", lightSpecular);

		m_Shader->SetUniform1f("material.shininess", 256.0f);

		m_Shader->SetUniform1f("light.constant", 1.0f);
		m_Shader->SetUniform1f("light.linear", 0.09f);
		m_Shader->SetUniform1f("light.quadratic", 0.032f);

		glm::mat4 vp = m_Proj * m_View;
		light[0]->OnRender(vp);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);

			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, 2.0f * (float)(glfwGetTime()) * glm::radians(angle), glm::vec3(0.2f, 1.0f, 0.3f));

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_Model", model);

			//renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			m_VAO->Bind();
			m_VertexBuffer->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void TestLighting::OnImGuiRender()
	{
		light[0]->OnImGuiRender();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Press C to control direction with mouse"
			"\nPress N to realease directional control"
			"\nPress M to access menu"
			"\nPress 2 to enter polygon mode"
			"\nPress 1 to return to normal mode"
			"\nPress esc to leave");
	}
}