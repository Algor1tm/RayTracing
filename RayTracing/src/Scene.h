#pragma once

#include "Environment.h"
#include "ProjectionCamera.h"


struct Scene
{
public:
	Scene() = default;

	Scene(const ProjectionCamera& camera)
		: Camera(camera) {}

	void LoadSandBoxScene();
	void LoadSceneSpheres();

public:
	ProjectionCamera Camera;
	GameObjectList Objects;
};