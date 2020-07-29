import numpy as np
import skimage.io as io
import cv2 as cv

cap = cv.VideoCapture("../videoSamples/boyball.mp4")
w = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
h = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))
n_frames = int(cap.get(cv.CAP_PROP_FRAME_COUNT))

vid_slice = np.zeros((h, n_frames, 3)).astype(np.float)

x = int(w/2)
i = 0
while cap.isOpened():
    ret, frame = cap.read()
    if frame is None:
        break
    else:
        vid_slice[:, i] = np.array(frame[:, x]).astype(np.float)/255
    i+=1

cv.imshow("vid", vid_slice)
cv.waitKey(0)
cv.destroyAllWindows()
