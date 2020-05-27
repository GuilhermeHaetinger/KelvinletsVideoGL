#ifndef LINE_HEADER
#define LINE_HEADER

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Point.h"
#include "Logger/Logger.h"

class Line{
	private:
		GLfloat getInterpolationCoefficient(GLfloat z);
		vec3 interpolateInformation(vec3 infoA, vec3 infoB, GLfloat t);
		Point pointA, pointB;
	public:
		Line(Point pointA, Point pointB);
		vec3 interpolatePosition(GLfloat z);
		vec3 interpolateColor(GLfloat z);
};

#endif
