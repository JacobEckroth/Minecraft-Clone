#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class WorldObject
{

protected:
	glm::vec3 position;
	glm::mat4 translation;
	

public:

	glm::vec3 getPosition();
	void setPosition(glm::vec3);
	virtual void render() = 0;
};

