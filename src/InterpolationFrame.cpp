#include "../include/InterpolationFrame.h"

void vec3ToFloatArray(GLfloat * array, int index, vec3 vector);
///

GLfloat * InterpolationFrame::getInterpolatedArray(TypeOfArray type){
	GLfloat * array = (GLfloat *)malloc(this->numberOfLines * 3 * sizeof(GLfloat));
	for(int line = 0, counter = 0; line < this->numberOfLines; line++, counter+=3){
		vec3 interpolatedPosition = this->getInterpolation(type, line);
		vec3ToFloatArray(array, counter, interpolatedPosition);
	}
	return array;
}

vec3 InterpolationFrame::getInterpolation(TypeOfArray type, int line){
	return type == POSITION ?
		this->lines[line].interpolatePosition(this->frameIndex) :
		this->lines[line].interpolateColor(this->frameIndex);
}

InterpolationFrame::InterpolationFrame(int width, int height, int frameIndex){
	this->frameIndex = frameIndex;
	this->numberOfLines = width * height;
	this->lines = (Line *)malloc(numberOfLines * sizeof(Line)); 
	this->index = 0;
}

void InterpolationFrame::addLine(Line line){
	this->lines[this->index] = line;
	this->index++;
}


GLfloat * InterpolationFrame::getInterpolatedVertexArray(){
	
	GLfloat * interp3D = this->getInterpolatedArray(this->TypeOfArray::POSITION);
	GLfloat * newInterp = (GLfloat *) malloc(this->numberOfLines * 2 * sizeof(GLfloat));
	
	for(int counter = 0; counter < this->numberOfLines; counter++){
		newInterp[counter*2] = interp3D[counter*3];
		newInterp[counter*2 + 1] = interp3D[counter*3 + 1];
	}
	free(interp3D);
	return newInterp;
}

GLfloat * InterpolationFrame::getInterpolatedColorArray(){
	return this->getInterpolatedArray(this->TypeOfArray::COLOR);
}

///
void vec3ToFloatArray(GLfloat * array, int index, vec3 vector){
	
//	printf("%lf\n", vector[0]);
	
	array[index] = vector[0];
	array[index + 1] = vector[1];
	array[index + 2] = vector[2];
}
