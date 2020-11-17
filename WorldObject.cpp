#include "WorldObject.h"


glm::vec3 WorldObject::getPosition() {
	return position;
}

void WorldObject::setPosition(glm::vec3 newPos) {
	position = newPos;
	translation = glm::mat4(1);
	translation = glm::translate(translation, position);
	

}