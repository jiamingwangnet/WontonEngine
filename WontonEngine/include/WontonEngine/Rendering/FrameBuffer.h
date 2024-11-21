#pragma once

// Basic Framebuffer
// TODO: add documentation and specifications
namespace won
{
	class FrameBuffer
	{
	public:
		FrameBuffer() = default;

		void Generate(unsigned int width, unsigned int height, unsigned int texloc, bool nearest = true);

		void SetAsTarget();
		void ActivateTexture();
		unsigned int GetTextureLocation();
		void Resize(unsigned int width, unsigned int height);

	private:
		unsigned int width, height;
		unsigned int texloc;
		unsigned int fbo;
		unsigned int rtex; // render texture
		unsigned int rbo; // render buffer for stencil and depth
	};
}