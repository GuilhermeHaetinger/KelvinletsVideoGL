#include "../include/Deformation.h"

using namespace glm;

Deformation::Deformation(vec3 initialPosition, vec3 finalPosition, float radius){
	this->initialPosition = initialPosition;
	this->finalPosition = finalPosition;
	this->radius = radius;
}

vec3 Deformation::getDeformationVector(){return this->finalPosition - this->initialPosition;}
vec3 Deformation::getInitialPosition(){return this->initialPosition;}
vec3 Deformation::getFinalPosition(){return this->finalPosition;}
float Deformation::getRadius(){return this->radius;}
