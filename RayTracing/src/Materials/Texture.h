#pragma once

#include "PerlinNoise.h"

#include <memory>
#include <string>


class Texture
{
public:
	virtual glm::vec3 Value(glm::vec2 texCoords, const glm::vec3& point) const = 0;
};


class SolidColor : public Texture
{
public:
	SolidColor() = default;
	SolidColor(const glm::vec3& color);

	glm::vec3 Value(glm::vec2 texCoords, const glm::vec3& point) const override;

private:
	glm::vec3 m_Color;
};


class CheckerTexture : public Texture
{
public:
	CheckerTexture(const glm::vec3& even, const glm::vec3& odd);
	CheckerTexture(const std::shared_ptr<Texture>& even, const std::shared_ptr<Texture>& odd);

	glm::vec3 Value(glm::vec2 texCoords, const glm::vec3& point) const override;

private:
	std::shared_ptr<Texture> m_Even;
	std::shared_ptr<Texture> m_Odd;
};


class NoiseTexture : public Texture
{
public:
	NoiseTexture() = default;
	NoiseTexture(float scale);

	glm::vec3 Value(glm::vec2 texCoords, const glm::vec3& point) const override;

private:
	Perlin m_Noise;
	float m_Scale;
};


class ImageTexture: public Texture
{
public:
	ImageTexture(const std::string& path);
	~ImageTexture();

	glm::vec3 Value(glm::vec2 texCoords, const glm::vec3& point) const override;

private:
	unsigned char* m_Data;
	uint32_t m_Width, m_Height;
	const int m_BytesPerPixel = 3;
};
