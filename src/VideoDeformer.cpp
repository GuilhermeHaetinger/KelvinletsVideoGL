#include "../include/VideoDeformer.h"

VideoDeformer::VideoDeformer(Deformation deformation, Frame * frames, Proportions proportions) :
	kelvinletsTransformer(deformation, 1.0f, 0.4f), proportions(proportions)
{
	Logger::log_debug("Creating VideoDeformer!");
	int sizeOfFrameArray = this->proportions.length * sizeof(Frame);
	this->frames = (Frame *) malloc(this->proportions.length * sizeof(Frame));
	memcpy(this->frames, frames, sizeOfFrameArray);

	this->depthValue = (GLfloat **) malloc(this->proportions.length * sizeof(GLfloat *));
	for(int i = 0; i < this->proportions.length; i++)
		this->depthValue[i] = (GLfloat *) malloc(this->proportions.width * this->proportions.height * sizeof(GLfloat));
		
	Logger::log_correct("Created VideoDeformer!");
}

Frame * VideoDeformer::generateInterpolatedFrames(Frame * frames){
	Logger::log_debug("Entering interpolated frames generation function!");
	Logger::log_debug("Setting new Color matrix!");
	int colorArraySize = this->proportions.width * this->proportions.height * 3 * sizeof(GLfloat);
	GLfloat ** newColorMatrix = (GLfloat **) malloc(this->proportions.length * sizeof(GLfloat *));
	for(int frame = 0; frame < this->proportions.length; frame++) 	
			newColorMatrix[frame] = (GLfloat *) malloc(colorArraySize);

	Logger::log_debug("Creating Interpolated frames!");
	for(int y = 0; y < this->proportions.height; y++)
		for(int x = 0; x < this->proportions.width; x++){
			int currentPoint = 0;
			for(int z = 0; z < this->proportions.length - 1;){
				int index = y * this->proportions.width + x;
				int indexOn2Dimensions = index * 2; 
				int indexOn3Dimensions = index * 3; 
				GLfloat distToFrame = this->depthValue[currentPoint][index] - z;
				GLfloat distToPoint = abs(this->depthValue[currentPoint][index] - 
																	this->depthValue[currentPoint + 1][index]);
				if(abs(distToFrame) <= distToPoint || distToFrame > 0){
					glm::vec2 firstXYPosition = frames[currentPoint].getPosition(x, y, this->proportions.width);
					glm::vec3 firstPosition = glm::vec3(firstXYPosition, depthValue[currentPoint][index]);
					glm::vec3 firstColor = frames[currentPoint].getColor(x, y, this->proportions.width);
					Point first = Point(firstPosition, firstColor);	
					glm::vec2 secondXYPosition = frames[currentPoint + 1].getPosition(x, y, this->proportions.width);
					glm::vec3 secondPosition = glm::vec3(secondXYPosition, depthValue[currentPoint + 1][index]);
					glm::vec3 secondColor = frames[currentPoint + 1].getColor(x, y, this->proportions.width);
					Point second = Point(secondPosition, secondColor);

					Line line = Line(first, second);

					glm::vec3 interpolatedPosition = line.interpolatePosition((GLfloat) z);
					glm::vec3 interpolatedColor = line.interpolateColor((GLfloat) z);

					frames[z].vertexArray[indexOn2Dimensions] = interpolatedPosition[0];	
					frames[z].vertexArray[indexOn2Dimensions + 1] = interpolatedPosition[1];	
	
//				  printf("%lf -- %lf\n", interpolatedPosition[0], interpolatedPosition[1]);

					newColorMatrix[z][indexOn3Dimensions] = interpolatedColor[0];	
					newColorMatrix[z][indexOn3Dimensions + 1] = interpolatedColor[1];	
					newColorMatrix[z][indexOn3Dimensions + 2] = interpolatedColor[2];	
					
//					printf("%lf -- %lf -- %lf\n", interpolatedColor[0], interpolatedColor[1], interpolatedPosition[2]);
					
					z++;
				}else{
					currentPoint++;
				}
			}
			//TODO TREAR LAST FRAME CASE
		}
	Logger::log_correct("Created Interpolated frames!");
	for(int frame = 0; frame < this->proportions.length; frame++){
		free(frames[frame].colorArray);
		frames[frame].colorArray = (GLfloat *) malloc(colorArraySize);
		memcpy(frames[frame].colorArray, newColorMatrix[frame], colorArraySize);
		frames[frame].colorArray = newColorMatrix[frame];
	}
	return frames;
}

Frame * VideoDeformer::deform(Deformation deformation){
	for(int y = 0; y < this->proportions.height; y++)
		for(int x = 0; x < this->proportions.width; x++)
			for(int z = 0; z < this->proportions.length; z++){
				int index = y * this->proportions.width + x;
				
				glm::vec2 xyPosition = frames[z].getPosition(x, y, this->proportions.width);
				glm::vec3 newPosition = this->kelvinletsTransformer.grab(glm::vec3(xyPosition, (GLfloat) z));
			
				//printf("%lf -- %lf -- %lf\n", newPosition[0], newPosition[1], newPosition[2]);
				//getchar();
					
				int indexOn2Dimensions = (y * this->proportions.width + x) * 2;
				this->frames[z].vertexArray[indexOn2Dimensions] = newPosition[0]; 
				this->frames[z].vertexArray[indexOn2Dimensions + 1] = newPosition[1];				
				this->depthValue[z][index] = newPosition[2];	
			}

	Frame * interp = generateInterpolatedFrames(this->frames);
	return interp;
}
