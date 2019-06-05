#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <iostream>
#include "../include/Logger/Logger.h"
#include "../include/Line.h"

int main(){
	
	Point a = Point(vec3(1, 2, 3), vec3(0.0f, 0.0f, 0.0f));
	Point b = Point(vec3(2, 3, 7), vec3(1.0f, 1.0f, 1.0f));

	Line line = Line(a, b);

	vec3 pos = line.interpolatePosition(5.0f); 
	
	printf("%lf -- %lf -- %lf\n", pos[0], pos[1], pos[2]);

	return 0;
}

