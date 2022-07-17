#include "Image.h"
#include "Core/Debug.h"

#include <glad/glad.h>


static GLenum ImageFormatToOpenGLFormat(ImageFormat format)
{
	switch (format)
	{
	case ImageFormat::RGB:  return GL_RGB;
	case ImageFormat::RGBA: return GL_RGBA;
	}

	ASSERT(false, "Not supported image format");
	return 0;
}

Image::Image(uint32_t width, uint32_t height, ImageFormat format)
	: m_Width(width), m_Height(height)
{
	m_DataFormat = ImageFormatToOpenGLFormat(format);

	if (m_DataFormat == GL_RGBA)
		m_InternalFormat = GL_RGBA8;
	else if (m_DataFormat == GL_RGB)
		m_InternalFormat = GL_RGB8;

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Image::~Image()
{
	glDeleteTextures(1, &m_TextureID);
}

void Image::SetData(const void* data, uint32_t size)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void Image::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Image::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
