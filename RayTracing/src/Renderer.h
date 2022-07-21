#pragma once

#include "Image.h"
#include "Scene.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>


class Renderer
{
public:
	Renderer() = delete;

	static void Render(const std::shared_ptr<Scene>& scene);
	static void OnResize(uint32_t width, uint32_t height);
	static const std::unique_ptr<Image>& GetFinalImage() { return m_FinalImage; }

private:
	static glm::vec4 FragmentShader(glm::vec2 coord);
	static glm::vec4 PostProcess(const glm::vec3& color);

private:
	struct RendererProps
	{
		static constexpr uint32_t SamplesPerPixel = 5;
		static constexpr uint32_t ChildRaysCount = 8;
	};

private:
	static std::unique_ptr<Image> m_FinalImage;
	static std::vector<uint32_t> m_ImageData;

	static std::shared_ptr<Scene> m_Scene;
};
