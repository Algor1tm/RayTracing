#pragma once

#include "Environment.h"
#include "ProjectionCamera.h"


struct Scene
{
public:
	Scene() = default;

	Scene(const ProjectionCamera& camera)
		: Camera(camera) {}

public:
	ProjectionCamera Camera;
	GameObjectList Objects;
};