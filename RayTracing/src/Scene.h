#pragma once

#include "Objects/GameObject.h"
#include "ProjectionCamera.h"


struct Scene
{
public:
	Scene() = default;

	Scene(const ProjectionCamera& camera)
		: Camera(camera) {}

	void LoadSandBoxScene();
	void LoadFinalScene();
	void LoadCornellBoxScene();
	void LoadSpheresScene();


public:
	ProjectionCamera Camera;
	GameObjectList Objects;
	glm::vec3 Background;
};
