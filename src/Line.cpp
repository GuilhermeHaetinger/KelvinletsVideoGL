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
	
//	printf("%lf -- %lf -- %lf\n", z, this->pointA.getPosition()[2], this->pointB.getPosition()[2]);

	return zPositionRelativeToA / totalZDistance;
}

vec3 Line::interpolateInformation(vec3 infoA, vec3 infoB, GLfloat t){
	//printf("%lf -- %lf -- %lf\n", infoA[0], infoA[1], infoA[2]);
	//printf("%lf -- %lf -- %lf\n", infoB[0], infoB[1], infoB[2]);
	//printf("%lf\n\n", t);
	
	return t * infoA + (1 - t) * infoB;
}

vec3 Line::interpolatePosition(GLfloat z){
		GLfloat t = getInterpolationCoefficient(z);
//	printf("%lf -- %lf -- %lf\n", this->pointA.getPosition()[0], this->pointA.getPosition()[1], this->pointA.getPosition()[2]);
		return interpolateInformation(this->pointA.getPosition(), this->pointB.getPosition(), t);
}

vec3 Line::interpolateColor(GLfloat z){
		GLfloat t = getInterpolationCoefficient(z);
		return interpolateInformation(this->pointA.getColor(), this->pointB.getColor(), t);
}
