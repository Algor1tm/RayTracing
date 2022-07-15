#include "Application.h"


class RayTracing : public Layer
{
	void OnAttach()
	{

	}

	void OnDetach()
	{

	}

	void OnImGuiRender()
	{

	}

	void OnUpdate(Time frameTime)
	{

	}
};

class RayTracingApplication : public Application
{
public:
	RayTracingApplication()
	{
		PushLayer(new RayTracing());
	}
};


Application* CreateApplication()
{
	return new RayTracingApplication();
}
