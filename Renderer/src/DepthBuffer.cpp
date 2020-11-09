#include "DepthBuffer.h"
#include "Renderer.h"

DepthBuffer::DepthBuffer(const void * data, unsigned int size)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));   // Generate 1 buffer with ID


	GLCall(glGenTextures(1, &depthMapID));

	GLCall(glBindTexture(GL_TEXTURE_2D, depthMapID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCall(glBindBuffer(GL_FRAMEBUFFER, m_RendererID));     /*Bind buffer to a type. It is now an array. It can aslo be drawn*/
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapID, 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));

	Unbind();
}

DepthBuffer::~DepthBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

void DepthBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_FRAMEBUFFER, m_RendererID));
}

void DepthBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_FRAMEBUFFER, 0));
}
