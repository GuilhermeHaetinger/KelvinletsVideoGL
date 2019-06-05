#ifndef POINT_HEADER
#define POINT_HEADER

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Logger/Logger.h"

using namespace glm;

class Point{
	private:
		vec3 position;
		vec3 color;
	public:
		Point(vec3 position, vec3 color);
		vec3 getPosition();
		vec3 getColor();
};

#endif
