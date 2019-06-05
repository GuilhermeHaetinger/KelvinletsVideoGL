#ifndef DEFORMATION_HEADER
#define DEFORMATION_HEADER

#include <glm/vec3.hpp>

#include "Logger/Logger.h"

using namespace glm;

class Deformation{
	private:
		vec3 initialPosition;
		vec3 finalPosition;
		float radius;
	public:
		Deformation(vec3 initialPosition, vec3 finalPosition, float radius);
		vec3 getDeformationVector();
		vec3 getInitialPosition();
		vec3 getFinalPosition();
		float getRadius();
};

#endif
