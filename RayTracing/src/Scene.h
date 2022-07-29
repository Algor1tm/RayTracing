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
	void LoadPerlinNoiseScene();
	void LoadCornellBoxScene();
	void LoadFinalScene();
	void LoadSpheresScene();


public:
	ProjectionCamera Camera;
	GameObjectList Objects;
	glm::vec3 Background;
};
