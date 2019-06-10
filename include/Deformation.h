#ifndef DEFORMATION_HEADER
#define DEFORMATION_HEADER

#include <glm/vec3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>

#include "Logger/Logger.h"

using namespace glm;

class Deformation{
	private:
		vec3 initialPosition;
		vec3 forceVector;
		float radius;
	public:
		Deformation(vec3 initialPosition, vec3 force, float radius);
		vec3 getInitialPosition();
		vec3 getForce();
		float getRadius();
};

#endif
