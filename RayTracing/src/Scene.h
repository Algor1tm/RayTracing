#include "Environment.h"

#include <vector>
#include <memory>


struct Scene
{
public:
	Scene()
		: Light(glm::vec3(0, 0, -1)) {}

public:
	std::vector<std::shared_ptr<GameObject>> Objects;
	DirectionalLight Light;
};