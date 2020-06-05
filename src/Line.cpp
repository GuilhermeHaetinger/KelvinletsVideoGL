#include "../include/Line.h"

Line::Line(Point pointA, Point pointB) : 
	pointA(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f)),
	pointB(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f))
{
	this->pointA = pointA;
	this->pointB = pointB;
}

GLfloat Line::getInterpolationCoefficient(GLfloat z){
	float zPositionRelativeToA = abs(z - this->pointA.getPosition()[2]);
	float totalZDistance = abs(this->pointB.getPosition()[2] - this->pointA.getPosition()[2]);
	// std::cout << "Z: " << z << ", A:" << this->pointA.getPosition()[2] << ", B: " << this->pointB.getPosition()[2] << std::endl;
	return zPositionRelativeToA / totalZDistance;
}

vec3 Line::interpolateInformation(vec3 infoA, vec3 infoB, GLfloat t){
	return t * infoB + (1 - t) * infoA;
}

vec3 Line::interpolatePosition(GLfloat z){
	GLfloat t = getInterpolationCoefficient(z);
	// std::cout << t << std::endl;
	// getchar();
	return interpolateInformation(this->pointA.getPosition(), this->pointB.getPosition(), t);
}

vec3 Line::interpolateColor(GLfloat z){
	GLfloat t = getInterpolationCoefficient(z);
	vec3 interp = interpolateInformation(this->pointA.getColor(), this->pointB.getColor(), t);
	return interp;
}
