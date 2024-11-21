#include "include/WontonEngine/Rendering/FrameBuffer.h"
#include <glad/glad.h>
#include <stdexcept>

void won::FrameBuffer::Generate(unsigned int width, unsigned int height, unsigned int texloc)
{
	this->width = width;
	this->height = height;
	this->texloc = texloc;

	// generate buffers
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// generate texture
	glGenTextures(1, &rtex);
	glBindTexture(GL_TEXTURE_2D, rtex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// attach texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rtex, 0);

	// renderbuffer for stencil and depth
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Framebuffer is not complete" };

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void won::FrameBuffer::SetAsTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void won::FrameBuffer::ActivateTexture()
{
	glActiveTexture(GL_TEXTURE0 + texloc);
	glBindTexture(GL_TEXTURE_2D, rtex);
}

unsigned int won::FrameBuffer::GetTextureLocation()
{
	return texloc;
}

void won::FrameBuffer::Resize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, rtex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}
