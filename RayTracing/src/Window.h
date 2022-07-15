#pragma once

#include <cstdint>


struct GLFWwindow;

class Window
{
public:
	Window(uint32_t width, uint32_t height, bool vsync = true);
	~Window();

	void OnUpdate();

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	void SetVSync(bool enabled);
	inline bool IsVSync() const { return m_VSync; }

	inline void* GetNativeWindow() { return m_Window; }
	bool ShouldClose();

private:
	GLFWwindow* m_Window;
	uint32_t m_Width;
	uint32_t m_Height;
	bool m_VSync;
};