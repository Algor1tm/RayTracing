#pragma once

#include "Image.h"
#include "Scene.h"
#include "ThreadPool.h"
#include "Core/Time.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>


struct RendererProps
{
	uint32_t SamplesPerPixel;
	uint32_t ChildRaysCount;
	uint32_t ThreadsCount;
};


enum class RendererState
{
	Nothing = 0,
	Rendering = 1
};

class Renderer
{
public:
	Renderer() = delete;

	static void Init(const RendererProps& props);
	static void Shutdown();

	static void Render(const std::shared_ptr<Scene>& scene);
	static void OnResize(uint32_t width, uint32_t height);
	static void UpdateImage();

	static inline const std::unique_ptr<Image>& GetFinalImage() { return m_FinalImage; }
	static inline RendererState GetCurrentState() { return m_CurrentState; }
	static inline Time GetRenderTime() { return m_RenderTime; }

private:
	static void RenderRange(const std::shared_ptr<Scene>& scene, uint32_t startRow, uint32_t endRow);

	static glm::vec4 FragmentShader(glm::vec2 coord);
	static glm::vec3 RayColor(const Ray& ray, uint32_t depth);
	static glm::vec4 PostProcess(const glm::vec3& color);

private:
	static std::unique_ptr<Image> m_FinalImage;
	static std::vector<uint32_t> m_ImageData;

	static std::shared_ptr<Scene> m_Scene;
	static RendererProps m_RendererProps;

	static ThreadPool m_Pool;
	static RendererState m_CurrentState;
	static Time m_RenderTime;
};
