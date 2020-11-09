#include "LightSource.h"

#include "imgui/imgui.h"

namespace light {

	LightSource::LightSource(std::shared_ptr<VertexBuffer> VBO)
		: m_VertexBuffer(VBO), Scale(0.2f)
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);


		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/LightSource.shader");

		m_SourceCara.SourcePos = glm::vec3(1.0f, 1.0f, 1.3f);
		m_SourceCara.SourceAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
		m_SourceCara.SourceDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		m_SourceCara.SourceSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

	}

	LightSource::~LightSource()
	{
	}

	void LightSource::OnRender(const glm::mat4& vp)
	{
		m_Shader->Bind();
		m_VAO->Bind();
		m_VertexBuffer->Bind();

		//m_SourceCara.SourcePos = glm::vec3(6 * cos(glfwGetTime() * 2), 0.0f, 6 * sin(glfwGetTime() * 2));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_SourceCara.SourcePos);
		model = glm::scale(model, glm::vec3(Scale));
		m_Shader->SetUniformMat4f("u_Model", model);
		SetVP(vp);

		m_Shader->SetUniformVec3fv("u_LightColor", m_SourceCara.SourceDiffuse);


		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_Shader->Unbind();
	}

	void LightSource::OnImGuiRender()
	{
		ImGui::SliderFloat("Light Scale", &Scale, 0.0f, 2.0f);
		ImGui::SliderFloat3("Light Color", &m_SourceCara.SourceDiffuse.x, 0.0f, 1.0f);
		m_SourceCara.SourceAmbient = m_SourceCara.SourceDiffuse * glm::vec3(0.15);
		//m_SourceCara.SourceSpecular = m_SourceCara.SourceDiffuse;

		ImGui::SliderFloat3("Light Position", &m_SourceCara.SourcePos.x, -20.0f, 20.0f);

	}

	glm::vec3 LightSource::GetLightDiffuse()
	{
		return m_SourceCara.SourceDiffuse;
	}

	glm::vec3 LightSource::GetLightPos()
	{
		return m_SourceCara.SourcePos;
	}

	glm::vec3 LightSource::GetLightAmbient()
	{
		return m_SourceCara.SourceAmbient;
	}
	glm::vec3 LightSource::GetLightSpecular()
	{
		return m_SourceCara.SourceSpecular;
	}

	void LightSource::SetLightCara(glm::vec3 Pos, glm::vec3 Diffuse, glm::vec3 Specular)
	{
		m_SourceCara.SourcePos = Pos;
		m_SourceCara.SourceAmbient = Diffuse * glm::vec3(0.15f);
		m_SourceCara.SourceDiffuse = Diffuse;
		m_SourceCara.SourceSpecular = Specular;
	}

	void LightSource::SetVP(const glm::mat4& vp)
	{
		m_Shader->SetUniformMat4f("u_VP", vp);
	}
}