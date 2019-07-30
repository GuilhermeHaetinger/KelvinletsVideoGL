#include "../include/VideoDeformer.h"

int * frameCount;

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

  frameCount = (int *) malloc(this->proportions.length * sizeof(int));
  for(int i = 0; i < this->proportions.length; i++)
    frameCount[i] = 0;
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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void VideoDeformer::drawPoints() {

	Logger::log_debug("Initializing GLFW!");
	if(!glfwInit()){
		Logger::log_fatal("Couldn't initialize GLFW!");
		exit(1);
	}else
		Logger::log_correct("Initialized GLFW");

	Logger::log_debug("Initializing Window!");

  GLFWwindow * glWindow = glfwCreateWindow(this->proportions.width, this->proportions.height,
                                           "KELVINLETS VIDEO", NULL, NULL);
  glfwSetFramebufferSizeCallback(glWindow, FramebufferSizeCallback);
  if(!glWindow){
		Logger::log_fatal("Couldn't initialize Window!");
		exit(1);
	}else{
		glfwMakeContextCurrent(glWindow);
		Logger::log_correct("Initialized Window!");
	}

	Logger::log_debug("Initializing GLEW!");
	if(glewInit() != GLEW_OK){
		Logger::log_fatal("Couldn't initialize GLEW!");
		exit(1);
	}else
		Logger::log_correct("Initialized GLEW");

  GLuint vtxBuf;
  GLuint clrBuf;
  GLuint idxBuf;

	glGenBuffers(1, &vtxBuf);
	glGenBuffers(1, &clrBuf);
	glGenBuffers(1, &idxBuf);

  //VTX
	Logger::log_debug("Initializing Vertex Buffer data!");
	int vertexDataSize = this->proportions.width * this->proportions.height * this->proportions.length * 3 * sizeof(GLfloat);
	GLfloat * vertexArray = (GLfloat *)malloc(vertexDataSize);

  //CLR
	Logger::log_debug("Initializing Color Buffer data!");
	int colorDataSize = this->proportions.width * this->proportions.height * this->proportions.length * 3 * sizeof(GLfloat);
	GLfloat * colorArray = (GLfloat *) malloc(colorDataSize);

  //IDX
  Logger::log_debug("Initializing index Buffer data!");
  int sz = this->proportions.length * this->proportions.width * this->proportions.height * sizeof(GLuint);
  GLuint * idx = (GLuint *) malloc(sz);

  for(int z = 0; z < this->proportions.length; z++)
    for (int y = 0; y < this->proportions.height; y++)
      for (int x = 0; x < this->proportions.width; x++) {
        int index = z * this->proportions.height * this->proportions.width + y * this->proportions.width + x;
        idx[index] = index;
      }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sz, idx, GL_STATIC_DRAW);

  //SHADER
	Logger::log_debug("Initializing Shaders!");
	const char * vertexShaderPath = "shaders/vertexShader.glsl";
	const char * fragmentShaderPath = "shaders/fragmentShader.glsl";

	string vertexShader = ParseShader(vertexShaderPath);
	string fragmentShader = ParseShader(fragmentShaderPath);

	int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
  Logger::log_correct("Initialized Shaders!");

  // EXEC

	Logger::log_debug("Initializing Shifts!");
  int frameIndexShift[this->proportions.length];
  frameIndexShift[0] = 0;
  for(int i = 1; i < this->proportions.length; i++) {
    frameIndexShift[i] = frameIndexShift[i-1] + frameCount[i-1];
  }
  Logger::log_correct("Initialized Shifts!");

	Logger::log_debug("Initializing Fillings!");
  int frameFilling[this->proportions.length];
  for(int i = 0; i < this->proportions.length; i++)
    frameFilling[i] = 0;
  Logger::log_correct("Initialized Fillings!");

	Logger::log_debug("Creating Deformed Vertices!");
  for (int z = 0; z < this->proportions.length; z++) {
    for (int y = 0; y < this->proportions.height; y++) {
      for (int x = 0; x < this->proportions.width; x++) {
        int fullIndex = z * this->proportions.height * this->proportions.width + this->proportions.width * y + x;
        int index = this->proportions.width * y + x;
        int index2D = index * 2;
        int index3D = index * 3;


        glm::vec2 positionXY = this->frames[z].getPosition(x, y, this->proportions.width);
        int pixelFrame = round(this->depthValue[z][index]);
        if(pixelFrame >= 0 && pixelFrame < this->proportions.length) {
          vertexArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3] = positionXY.x;
          vertexArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3 + 1] = positionXY.y;
          vertexArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3 + 2] = 0;

          colorArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3] = this->frames[z].colorArray[index3D];
          colorArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3 + 1] = this->frames[z].colorArray[index3D + 1];
          colorArray[frameIndexShift[pixelFrame] * 3 + frameFilling[pixelFrame] * 3 + 2] = this->frames[z].colorArray[index3D + 2];

          frameFilling[pixelFrame]++;
        }
      }
    }
  }
  Logger::log_correct("Created Deformed Vertices!");

	glBindBuffer(GL_ARRAY_BUFFER, vtxBuf);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

	glBindBuffer(GL_ARRAY_BUFFER, clrBuf);
	glBufferData(GL_ARRAY_BUFFER, colorDataSize, colorArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

  while(true)
  for(int z = 0; z < this->proportions.length; z++) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(0.0001f);

    int frameSize = frameCount[z];

    glDrawElements(GL_POINTS, frameSize, GL_UNSIGNED_INT, (void *) (frameIndexShift[z] * sizeof(GLuint)));
    glfwSwapBuffers(glWindow);
    glfwPollEvents();
    getchar();
  }
}

Frame * VideoDeformer::deform(Deformation deformation){
  Logger::log_debug("Deforming Frames!");
	for(int y = 0; y < this->proportions.height; y++)
		for(int x = 0; x < this->proportions.width; x++)
			for(int z = 0; z < this->proportions.length; z++){
				int index = y * this->proportions.width + x;

				glm::vec2 xyPosition = frames[z].getPosition(x, y, this->proportions.width);
        glm::vec2 unorm = glm::vec2(((xyPosition.x + 1) / 2) * (this->proportions.width - 1),
                                   -(((xyPosition.y + 1) / 2) * (this->proportions.height - 1) + 1 - this->proportions.height));

        glm::vec3 newPosition = this->kelvinletsTransformer.grab(glm::vec3(unorm, (GLfloat) z));

        newPosition[0] = 2 * (newPosition[0] / (this->proportions.width - 1)) - 1;
        newPosition[1] =  2 * ((this->proportions.height - 1 - newPosition[1])/(this->proportions.height - 1)) - 1;

				int indexOn2Dimensions = (y * this->proportions.width + x) * 2;
				this->frames[z].vertexArray[indexOn2Dimensions] = newPosition[0];
				this->frames[z].vertexArray[indexOn2Dimensions + 1] = newPosition[1];
				this->depthValue[z][index] = newPosition[2];

        int framePos = round(newPosition[2]);
        if(framePos >= 0 && framePos < this->proportions.length)
          frameCount[framePos]++;

      }
  Logger::log_correct("Deformed Frames!");
  Logger::log_debug("Drawing Points!");
  this->drawPoints();

	Frame * interp = generateInterpolatedFrames(this->frames);
	return interp;
}
