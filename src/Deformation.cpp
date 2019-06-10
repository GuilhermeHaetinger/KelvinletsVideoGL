#include "../include/Deformation.h"

using namespace glm;

Deformation::Deformation(vec3 initialPosition, vec3 forceVector, float radius){
	this->initialPosition = initialPosition;
	this->forceVector = forceVector;
	this->radius = radius;
}

vec3 Deformation::getInitialPosition(){return this->initialPosition;}
vec3 Deformation::getForce(){return this->forceVector;}
float Deformation::getRadius(){return this->radius;}
