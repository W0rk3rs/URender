#include "TestSphere.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

#include "Renderer.h"


namespace test {

	TestSphere::TestSphere(GLFWwindow* window)
		:m_Proj(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0f))),
		m_Window(window)
	{
		m_Layers = 10;
		m_Radius = 5.0f;

		CacheLayers = m_Layers;
		//CacheRadius = m_Radius;

		GLCall(glEnable(GL_DEPTH_TEST)); // Very important for 3D

		m_Shader = std::make_unique<Shader>("res/shaders/SphereLighting.shader");

		m_Shader->Bind();

		texture.push_back(std::make_unique<Texture>("res/textures/earth.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/earth2.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/earth3.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/earth_specular.jpg"));
		texture.push_back(std::make_unique<Texture>("res/textures/earth_normal_map.png"));
		texture.push_back(std::make_unique<Texture>("res/textures/earth_normal_map_2.jpg"));


		texture.push_back(std::make_unique<Texture>("res/textures/nada.jpg"));


		m_Shader->SetUniform1i("materialDiffuse", 0);
		m_Shader->SetUniform1i("materialSpecular", 1);
		m_Shader->SetUniform1i("normalMap", 2);


		m_Shader->SetUniformVec3fv("material.specular", glm::vec3(0.8f));
		m_Shader->SetUniform1f("material.shininess", 32.0f);

		Camera::InitCamera((GLFWwindow*)m_Window, glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f, 0.0f);
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
			m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, 6 * 6 * 8 * sizeof(float));
			light.push_back(std::make_unique<light::LightSource>(m_VertexBuffer));
		}

		MakeSphereVertices();

		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		//m_IndexBuffer->Unbind();
		m_Shader->Unbind();

		light[0]->SetLightCara(glm::vec3(3.429f, 2.857f, 7.606f),
				glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f));

	}

	TestSphere::~TestSphere()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void TestSphere::OnUpdate(float deltaTime)
	{

	}

	void TestSphere::OnRender()
	{
		Camera::PollInput();

		m_Proj = glm::perspective(glm::radians(Camera::GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);

		m_View = Camera::GetViewMatrix();

		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//Renderer renderer;

		m_Shader->Bind();
		texture[0]->Bind(0);
		texture[3]->Bind(1);
		texture[5]->Bind(2);


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

		m_Shader->SetUniform1f("light.constant", 1.0f);
		m_Shader->SetUniform1f("light.linear", 0.09f);
		m_Shader->SetUniform1f("light.quadratic", 0.032f);

		glm::mat4 vp = m_Proj * m_View;


		light[0]->OnRender(vp);

		if (m_CacheCounter > 20) {
			if (m_Layers != CacheLayers)
			{	
				MakeSphereVertices();
				CacheLayers = m_Layers;
				//CacheRadius = m_Radius;
				m_CacheCounter = 0;
			}
		}
		if (m_CacheCounter < 30) {
			m_CacheCounter++;
		}

		glm::vec3 positions[] = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(7.0f, 2.0f, -6.0f) };

		for (int i = 0; i < 1; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), positions[i]);
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 1.0f * (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(m_Radius));

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_Model", model);

			//renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			m_VAO->Bind();
			m_VertexBuffer->Bind();
			glDrawArrays(GL_TRIANGLES, 0, m_TrianglesNumber);
		}
	}

	void TestSphere::OnImGuiRender()
	{
		light[0]->OnImGuiRender();
		ImGui::SliderFloat("Radius", &m_Radius, 0.5f, 10.0f);
		ImGui::SliderInt("Ball layers", &m_Layers, 10, 1000);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Application average %d triangles", m_TrianglesNumber / 3);
		ImGui::Text("Press C to control direction with mouse"
			"\nPress N to realease directional control"
			"\nPress M to access menu"
			"\nPress 2 to enter polygon mode"
			"\nPress 1 to return to normal mode"
			"\nPress esc to leave"
			"\nPress W,A,S,D to move the camera"
			"\nScroll up and down to zoom in and out");
	}

	void TestSphere::MakeSphereVertices()
	{
		float x, y, z;

		if (m_Layers < 10)
			m_Layers = 10;
		if (m_Layers % 2 == 1)
			m_Layers = m_Layers - 1;

		int VerticesBufferSize = ((m_Layers - 1) * (m_Layers / 2) + 2) * (3);
		int TexBufferSize = ((m_Layers - 1) * (m_Layers / 2) + 2) * (2);

		int IndicesBufferSize = (m_Layers)*(m_Layers - 1) * 3;

		m_TrianglesNumber = IndicesBufferSize;

		float* Vertices = new float[VerticesBufferSize];
		float* Textures = new float[TexBufferSize];

		unsigned int* Indices = new unsigned int[IndicesBufferSize];

		float* VertexCara = new float[IndicesBufferSize * 8];
		
		float* FinalVertexCara = new float[IndicesBufferSize * 11];

		float* GouradShading = new float[IndicesBufferSize * 3];
		int* GouradAverage = new int[IndicesBufferSize];

		//Init of GouradShading
		for (int i = 0; i < (IndicesBufferSize * 3); i++)
		{
			GouradShading[i] = 0;
		}

		//Init of GouradAverage
		for (int i = 0; i < IndicesBufferSize; i++)
		{
			GouradAverage[i] = 0;
		}

		//float PI = glm::pi<float>();
		float PI = 180.0f;

		//Vertices------------------------------------------------------------------
		for (int layer = 0; layer <= m_Layers; layer++)
		{
			z = 1 * cos(glm::radians((PI / m_Layers) * layer));

			if (layer == 0)
			{
				x = 0.0f;
				y = 0.0f;

				Vertices[0] = x;
				Vertices[1] = y;
				Vertices[2] = z;
				continue;
			}
			if (layer == m_Layers)
			{
				x = 0.0f;
				y = 0.0f;

				Vertices[VerticesBufferSize - 3] = x;
				Vertices[VerticesBufferSize - 2] = y;
				Vertices[VerticesBufferSize - 1] = z;
				continue;
			}

			for (int i = 0; i < m_Layers / 2; i++)
			{
				if (layer % 2 == 0)
				{
					x = 1 * sin(glm::radians((PI / m_Layers) * layer)) * cos(glm::radians((2 * i * PI) / (m_Layers / 2)));
					y = 1 * sin(glm::radians((PI / m_Layers) * layer)) * sin(glm::radians((2 * i * PI) / (m_Layers / 2)));

					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 0] = x;
					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 1] = y;
					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 2] = z;
					continue;
				}
				else
				{
					x = 1 * sin(glm::radians((PI / m_Layers) * layer)) * cos(glm::radians((((2 * i) + 0)* PI) / (m_Layers / 2)));
					y = 1 * sin(glm::radians((PI / m_Layers) * layer)) * sin(glm::radians((((2 * i) + 0)* PI) / (m_Layers / 2)));

					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 0] = x;
					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 1] = y;
					Vertices[3 + (((layer - 1) * (m_Layers / 2)) * 3) + (3 * i) + 2] = z;
					continue;
				}
			}
		}

		//Tex Coord----------------------------------------------------
		for (int layer = 0; layer <= m_Layers; layer++)
		{
			if (layer == 0)
			{
				Textures[0] = 0.5f;
				Textures[1] = 0.0f;
				continue;
			}
			if (layer == m_Layers)
			{

				Textures[TexBufferSize - 2] = 0.5f;
				Textures[TexBufferSize - 1] = 1.0f;
				continue;
			}

			for (int i = 0; i < m_Layers / 2; i++)
			{
				Textures[2 + (((layer - 1) * (m_Layers / 2)) * 2) + (2 * i) + 0] = (float)i / (m_Layers / 2);
				Textures[2 + (((layer - 1) * (m_Layers / 2)) * 2) + (2 * i) + 1] = (float)layer / m_Layers;
			}
		}

		//Indices-------------------------------------------------------------------
		for (int layer = 0; layer < m_Layers - 1; layer++)
		{
			if (layer == 0)
			{
				for (int i = 0; i < (m_Layers / 2); i++)
				{
					if (i == (m_Layers / 2) - 1)
					{
						Indices[3 * i + 0] = 0;
						Indices[3 * i + 1] = i + 1;
						Indices[3 * i + 2] = 1;
						continue;
					}
					Indices[3 * i + 0] = 0;
					Indices[3 * i + 1] = i + 1;
					Indices[3 * i + 2] = i + 2;
				}
			}

			if (layer == m_Layers - 2)
			{
				for (int i = 0; i < (m_Layers / 2); i++)
				{
					if (i == (m_Layers / 2) - 1)
					{
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 0] = ((m_Layers / 2) * (m_Layers - 1)) + 1;
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 1] = (layer) * (m_Layers / 2) + 1;
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 2] = (layer) * (m_Layers / 2) + i + 1;
						continue;
					}
					Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 0] = ((m_Layers / 2) * (m_Layers - 1)) + 1;
					Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 1] = (layer) * (m_Layers / 2) + i + 2;
					Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * i + 2] = (layer) * (m_Layers / 2) + i + 1;
				}
			}

			else
			{
				for (int i = 1; i <= m_Layers; i++)
				{
					if (i <= (m_Layers / 2))
					{
						if (i == (m_Layers / 2))
						{
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 0] = layer * (m_Layers / 2) + i;
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 1] = (layer + 1) *(m_Layers / 2) + i;
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 2] = (layer + 1) *(m_Layers / 2) + 1;
							continue;
						}
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 0] = layer * (m_Layers / 2) + i;
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 1] = (layer + 1) *(m_Layers / 2) + i;
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 2] = (layer + 1) *(m_Layers / 2) + i + 1;
					}
					else
					{
						if (i == m_Layers)
						{
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 0] = (layer-1) * (m_Layers / 2) + i + 1;
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 1] = (layer-1) * (m_Layers / 2) + (i + 1 - (m_Layers / 2));
							Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 2] = layer *(m_Layers / 2) + (i - (m_Layers / 2));
							continue;
						}
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 0] = layer * (m_Layers / 2) + i + 1;
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 1] = layer * (m_Layers / 2) + (i + 1 - (m_Layers / 2));
						Indices[((m_Layers / 2) * 3) + (layer * m_Layers * 3) + 3 * (i - 1) + 2] = layer * (m_Layers / 2) + (i - (m_Layers / 2));
					}
				}
			}
		}

		//VertexCara: Vertices and normal and TexCoord-------------------------------------------
		for (int i = 0, triangle = 0; i < IndicesBufferSize; i++)
		{
			glm::vec3 pos, vec1, vec2, normal;

			if (i % 3 == 0)
				triangle += 1;

			if (i % 3 == 0)
			{
				pos.x = Vertices[3 * Indices[i]];
				pos.y = Vertices[3 * Indices[i] + 1];
				pos.z = Vertices[3 * Indices[i] + 2];

				vec1.x = Vertices[3 * Indices[i + 2]];
				vec1.y = Vertices[3 * Indices[i + 2] + 1];
				vec1.z = Vertices[3 * Indices[i + 2] + 2];

				vec2.x = Vertices[3 * Indices[i + 1]];
				vec2.y = Vertices[3 * Indices[i + 1] + 1];
				vec2.z = Vertices[3 * Indices[i + 1] + 2];

				vec1 = vec1 - pos;
				vec2 = vec2 - pos;
			}

			if (i % 3 == 1)
			{
				pos.x = Vertices[3 * Indices[i]];
				pos.y = Vertices[3 * Indices[i] + 1];
				pos.z = Vertices[3 * Indices[i] + 2];

				vec1.x = Vertices[3 * Indices[i - 1]];
				vec1.y = Vertices[3 * Indices[i - 1] + 1];
				vec1.z = Vertices[3 * Indices[i - 1] + 2];

				vec2.x = Vertices[3 * Indices[i + 1]];
				vec2.y = Vertices[3 * Indices[i + 1] + 1];
				vec2.z = Vertices[3 * Indices[i + 1] + 2];

				vec1 = vec1 - pos;
				vec2 = vec2 - pos;
			}

			if (i % 3 == 2)
			{
				pos.x = Vertices[3 * Indices[i]];
				pos.y = Vertices[3 * Indices[i] + 1];
				pos.z = Vertices[3 * Indices[i] + 2];

				vec1.x = Vertices[3 * Indices[i - 1]];
				vec1.y = Vertices[3 * Indices[i - 1] + 1];
				vec1.z = Vertices[3 * Indices[i - 1] + 2];

				vec2.x = Vertices[3 * Indices[i - 2]];
				vec2.y = Vertices[3 * Indices[i - 2] + 1];
				vec2.z = Vertices[3 * Indices[i - 2] + 2];

				vec1 = vec1 - pos;
				vec2 = vec2 - pos;
			}

			normal = glm::cross(vec2, vec1);

			if (triangle != 0 && (triangle % (m_Layers / 2) == 0) && triangle < (m_TrianglesNumber / 3))
			{

				if (triangle % m_Layers == m_Layers / 2)
				{
					VertexCara[8 * i + 0] = pos.x;
					VertexCara[8 * i + 1] = pos.y;
					VertexCara[8 * i + 2] = pos.z;
					VertexCara[8 * i + 3] = normal.x;
					VertexCara[8 * i + 4] = normal.y;
					VertexCara[8 * i + 5] = normal.z;
					VertexCara[8 * i + 6] = ((i % 3 == 0 || i % 3 == 1) ? 1.0f : Textures[2 * Indices[i]]);
					VertexCara[8 * i + 7] = Textures[2 * Indices[i] + 1];
				}
				else
				{
					VertexCara[8 * i + 0] = pos.x;
					VertexCara[8 * i + 1] = pos.y;
					VertexCara[8 * i + 2] = pos.z;
					VertexCara[8 * i + 3] = normal.x;
					VertexCara[8 * i + 4] = normal.y;
					VertexCara[8 * i + 5] = normal.z;
					VertexCara[8 * i + 6] = ((i % 3 == 2) ? 1.0f : Textures[2 * Indices[i]]);
					VertexCara[8 * i + 7] = Textures[2 * Indices[i] + 1];
				}
				continue;
			}
			
			if (i % 3 == 0)
			{
				VertexCara[8 * i + 0] = pos.x;
				VertexCara[8 * i + 1] = pos.y;
				VertexCara[8 * i + 2] = pos.z;
				VertexCara[8 * i + 3] = normal.x;
				VertexCara[8 * i + 4] = normal.y;
				VertexCara[8 * i + 5] = normal.z;
				VertexCara[8 * i + 6] = Textures[2 * Indices[i]];
				VertexCara[8 * i + 7] = Textures[2 * Indices[i] + 1];
		

				GouradShading[3 * Indices[i] + 0] += normal.x;
				GouradShading[3 * Indices[i] + 1] += normal.y;
				GouradShading[3 * Indices[i] + 2] += normal.z;

				GouradAverage[Indices[i]] += 1;

				continue;
			}

			if (i % 3 == 1)
			{
				VertexCara[8 * i + 0] = pos.x;
				VertexCara[8 * i + 1] = pos.y;
				VertexCara[8 * i + 2] = pos.z;
				VertexCara[8 * i + 3] = normal.x;
				VertexCara[8 * i + 4] = normal.y;
				VertexCara[8 * i + 5] = normal.z;
				VertexCara[8 * i + 6] = Textures[2 * Indices[i]];
				VertexCara[8 * i + 7] = Textures[2 * Indices[i] + 1];
		
				GouradShading[3 * Indices[i] + 0] += normal.x;
				GouradShading[3 * Indices[i] + 1] += normal.y;
				GouradShading[3 * Indices[i] + 2] += normal.z;

				GouradAverage[Indices[i]] += 1;
				continue;
			}

			if (i % 3 == 2)
			{
				VertexCara[8 * i + 0] = pos.x;
				VertexCara[8 * i + 1] = pos.y;
				VertexCara[8 * i + 2] = pos.z;
				VertexCara[8 * i + 3] = normal.x;
				VertexCara[8 * i + 4] = normal.y;
				VertexCara[8 * i + 5] = normal.z;
				VertexCara[8 * i + 6] = Textures[2 * Indices[i]];
				VertexCara[8 * i + 7] = Textures[2 * Indices[i] + 1];	

				GouradShading[3 * Indices[i] + 0] += normal.x;
				GouradShading[3 * Indices[i] + 1] += normal.y;
				GouradShading[3 * Indices[i] + 2] += normal.z;

				GouradAverage[Indices[i]] += 1;
				continue;
			}
		}

		//finalVertexCara
		for (int i = 0, triangle = 0; i < IndicesBufferSize; i++)
		{
			glm::vec3 edge1, edge2, tangent;
			glm::vec2 deltaUV1, deltaUV2;
			float invDet;

			if (i % 3 == 0)
			{
				FinalVertexCara[11 * i + 0] = VertexCara[8 * i + 0];
				FinalVertexCara[11 * i + 1] = VertexCara[8 * i + 1];
				FinalVertexCara[11 * i + 2] = VertexCara[8 * i + 2];
			//	FinalVertexCara[11 * i + 3] = VertexCara[8 * i + 3];
			//	FinalVertexCara[11 * i + 4] = VertexCara[8 * i + 4];
			//	FinalVertexCara[11 * i + 5] = VertexCara[8 * i + 5];
				FinalVertexCara[11 * i + 6] = VertexCara[8 * i + 6];
				FinalVertexCara[11 * i + 7] = VertexCara[8 * i + 7];


				edge1.x = VertexCara[8 * (i + 1) + 0] - VertexCara[8 * i + 0];
				edge1.y = VertexCara[8 * (i + 1) + 1] - VertexCara[8 * i + 1];
				edge1.z = VertexCara[8 * (i + 1) + 2] - VertexCara[8 * i + 2];

				edge2.x = VertexCara[8 * (i + 2) + 0] - VertexCara[8 * i + 0];
				edge2.y = VertexCara[8 * (i + 2) + 1] - VertexCara[8 * i + 1];
				edge2.z = VertexCara[8 * (i + 2) + 2] - VertexCara[8 * i + 2];

				deltaUV1.x = VertexCara[8 * (i + 1) + 6] - VertexCara[8 * i + 6];
				deltaUV1.y = VertexCara[8 * (i + 1) + 7] - VertexCara[8 * i + 7];

				deltaUV2.x = VertexCara[8 * (i + 2) + 6] - VertexCara[8 * i + 6];
				deltaUV2.y = VertexCara[8 * (i + 2) + 7] - VertexCara[8 * i + 7];

				invDet = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent.x = invDet * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent.y = invDet * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent.z = invDet * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

				FinalVertexCara[11 * i + 8] = tangent.x;
				FinalVertexCara[11 * i + 9] = tangent.y;
				FinalVertexCara[11 * i + 10] = tangent.z;
				
				continue;
			}

			if (i % 3 == 1)
			{
				FinalVertexCara[11 * i + 0] = VertexCara[8 * i + 0];
				FinalVertexCara[11 * i + 1] = VertexCara[8 * i + 1];
				FinalVertexCara[11 * i + 2] = VertexCara[8 * i + 2];
			//	FinalVertexCara[11 * i + 3] = VertexCara[8 * i + 3];
			//	FinalVertexCara[11 * i + 4] = VertexCara[8 * i + 4];
			//	FinalVertexCara[11 * i + 5] = VertexCara[8 * i + 5];
				FinalVertexCara[11 * i + 6] = VertexCara[8 * i + 6];
				FinalVertexCara[11 * i + 7] = VertexCara[8 * i + 7];


				edge1.x = VertexCara[8 * (i + 1) + 0] - VertexCara[8 * i + 0];
				edge1.y = VertexCara[8 * (i + 1) + 1] - VertexCara[8 * i + 1];
				edge1.z = VertexCara[8 * (i + 1) + 2] - VertexCara[8 * i + 2];

				edge2.x = VertexCara[8 * (i - 1) + 0] - VertexCara[8 * i + 0];
				edge2.y = VertexCara[8 * (i - 1) + 1] - VertexCara[8 * i + 1];
				edge2.z = VertexCara[8 * (i - 1) + 2] - VertexCara[8 * i + 2];

				deltaUV1.x = VertexCara[8 * (i + 1) + 6] - VertexCara[8 * i + 6];
				deltaUV1.y = VertexCara[8 * (i + 1) + 7] - VertexCara[8 * i + 7];

				deltaUV2.x = VertexCara[8 * (i - 1) + 6] - VertexCara[8 * i + 6];
				deltaUV2.y = VertexCara[8 * (i - 1) + 7] - VertexCara[8 * i + 7];

				invDet = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent.x = invDet * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent.y = invDet * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent.z = invDet * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

				FinalVertexCara[11 * i + 8] = tangent.x;
				FinalVertexCara[11 * i + 9] = tangent.y;
				FinalVertexCara[11 * i + 10] = tangent.z;
				continue;

			}

			if (i % 3 == 2)
			{
				FinalVertexCara[11 * i + 0] = VertexCara[8 * i + 0];
				FinalVertexCara[11 * i + 1] = VertexCara[8 * i + 1];
				FinalVertexCara[11 * i + 2] = VertexCara[8 * i + 2];
			//	FinalVertexCara[11 * i + 3] = VertexCara[8 * i + 3];
				//FinalVertexCara[11 * i + 4] = VertexCara[8 * i + 4];
				//FinalVertexCara[11 * i + 5] = VertexCara[8 * i + 5];
				FinalVertexCara[11 * i + 6] = VertexCara[8 * i + 6];
				FinalVertexCara[11 * i + 7] = VertexCara[8 * i + 7];


				edge1.x = VertexCara[8 * (i - 1) + 0] - VertexCara[8 * i + 0];
				edge1.y = VertexCara[8 * (i - 1) + 1] - VertexCara[8 * i + 1];
				edge1.z = VertexCara[8 * (i - 1) + 2] - VertexCara[8 * i + 2];

				edge2.x = VertexCara[8 * (i - 2) + 0] - VertexCara[8 * i + 0];
				edge2.y = VertexCara[8 * (i - 2) + 1] - VertexCara[8 * i + 1];
				edge2.z = VertexCara[8 * (i - 2) + 2] - VertexCara[8 * i + 2];

				deltaUV1.x = VertexCara[8 * (i - 1) + 6] - VertexCara[8 * i + 6];
				deltaUV1.y = VertexCara[8 * (i - 1) + 7] - VertexCara[8 * i + 7];
											   
				deltaUV2.x = VertexCara[8 * (i - 2) + 6] - VertexCara[8 * i + 6];
				deltaUV2.y = VertexCara[8 * (i - 2) + 7] - VertexCara[8 * i + 7];

				invDet = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangent.x = invDet * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
				tangent.y = invDet * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
				tangent.z = invDet * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

				FinalVertexCara[11 * i + 8] = tangent.x;
				FinalVertexCara[11 * i + 9] = tangent.y;
				FinalVertexCara[11 * i + 10] = tangent.z;
				continue;

			}
		}

		for (int i = 0, triangle = 0; i < IndicesBufferSize; i++)
		{
			FinalVertexCara[11 * i + 3] = GouradShading[3 * Indices[i] + 0] / (float)GouradAverage[Indices[i]];
			FinalVertexCara[11 * i + 4] = GouradShading[3 * Indices[i] + 1] / (float)GouradAverage[Indices[i]];
			FinalVertexCara[11 * i + 5] = GouradShading[3 * Indices[i] + 2] / (float)GouradAverage[Indices[i]];
		}

		m_VertexBuffer = std::make_shared<VertexBuffer>(FinalVertexCara, 11 * IndicesBufferSize * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);


		//m_IndexBuffer = std::make_unique<IndexBuffer>(Indices, IndicesBufferSize);
	
		delete[] Vertices;
		delete[] Indices;
		delete[] Textures;
		delete[] VertexCara;
		delete[] FinalVertexCara;
		delete[] GouradShading;
		delete[] GouradAverage;

	}
}