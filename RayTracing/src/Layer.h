#pragma once

#include "Time.h"

#include <memory>


struct LayerDeleter;

class Layer
{
public:
	using pointer_type = std::unique_ptr<Layer, LayerDeleter>;

public:
	virtual ~Layer() = default;

	virtual void OnAttach() {};
	virtual void OnDetach() {};

	virtual void OnUpdate(Time frameTime) {};
	virtual void OnImGuiRender() {};
};


struct LayerDeleter
{
	void operator()(Layer* layer)
	{
		if (layer != nullptr)
		{
			layer->OnDetach();
			delete layer;
		}
	}
};
