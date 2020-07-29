#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctime>
#include "../include/Logger/Logger.h"
#include "../include/VideoGL.h"
#include "../include/VideoDeformer.h"

using namespace std;
using namespace cv;


int main(int argc, char * argv[]){

	if(argc < 9) {
		cout << "Wrong format! Pleas input: ./kelvin [video_name] [x][y][z] [f_x][f_y][f_z] [radius]" << endl;
		exit(1);
	}
	char * video_name = argv[1];
	VideoCapture cap(video_name);
	if(!cap.isOpened()){
		Logger::log_error("Video wont open!");
	}

	Logger::log_debug("Entering Main function!");
	VideoGL video(video_name);
	
	Proportions prop = video.getProportions();
	Frame * frames = (Frame *) malloc(prop.length * sizeof(Frame));

	video.getFrames(frames);

	int x =      atoi(argv[2]);
	int y =      atoi(argv[3]);
	int z =      atoi(argv[4]);
	int f_x =    atoi(argv[5]);
	int f_y =    atoi(argv[6]);
	int f_z =    atoi(argv[7]);
	int radius = atoi(argv[8]);

	Deformation deformation(vec3(x, y, z), vec3(f_x, f_y, f_z), (GLfloat) radius);
	VideoDeformer * def = new VideoDeformer(deformation, frames, prop);

	time_t start = time(nullptr);

	Frame * newFrames = def->deform(deformation);

	time_t end = time(nullptr) - start;
	ostringstream buf;

	buf << "The deformation process took "
		 << end << " seconds" << endl;

	string msg(buf.str());
	Logger::log_correct(msg);

	video.resetFrames(newFrames);

	unsigned int fm = 50000;
	// while(true){
		video.show(fm);
		char com = getchar();
		// if(com == 'q')
			// break;
	// }

	// def->drawPoints();

	return 0;
}

