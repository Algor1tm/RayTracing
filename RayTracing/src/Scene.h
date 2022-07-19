#pragma once

#include "Environment.h"
#include "ProjectionCamera.h"

#include <vector>
#include <memory>


struct Scene
{
public:
	Scene(const ProjectionCamera& camera)
		: Light(glm::vec3(0, 0, -1)), Camera(camera) {}

public:
	ProjectionCamera Camera;

	std::vector<std::shared_ptr<GameObject>> Objects;
	DirectionalLight Light;
};