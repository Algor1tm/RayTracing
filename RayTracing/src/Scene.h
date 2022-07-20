#pragma once

#include "Environment.h"
#include "ProjectionCamera.h"


struct Scene
{
public:
	Scene(const ProjectionCamera& camera)
		: Light(glm::vec3(0, 0, -1)), Camera(camera) {}

public:
	ProjectionCamera Camera;

	GameObjectList Objects;
	DirectionalLight Light;
};