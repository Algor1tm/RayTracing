#pragma once

#include "Core/Layer.h"


class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void OnAttach() override;
	void OnDetach() override;

	void Begin();
	void End();
private:
	float m_Time = 0.f;
};
