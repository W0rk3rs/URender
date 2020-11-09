#pragma once

class DepthBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int depthMapID;

	const unsigned int SHADOW_WIDTH = 1024;
	const unsigned int SHADOW_HEIGHT = 1024;


public:
	DepthBuffer(const void* data, unsigned int size);
	~DepthBuffer();

	void Bind() const;
	void Unbind() const;
};