import cv2
import csk
from csk import *
import numpy as np
from imageio import imread, imsave
import time


# for my_pic2
ori_width = 1280
ori_height = 720
resize_width = 224
resize_height = 224
x1 = int(470 * (resize_width / ori_width)) # position x of the top-left corner of bounding box
# y1 = int(120 * (resize_height / ori_height)) # position y of the top-left corner of bounding box
y1 = 0
width = int(300 * (resize_width / ori_width)) # the width of bounding box
# height = int(380 * (resize_height / ori_height)) # the height of bounding box
height = int(ori_height * (resize_height / ori_height))
tracker = csk.CSK() # CSK instpance


# cap = cv2.VideoCapture(0)
cap = cv2.VideoCapture(1)
i = 0
while 1:
    ret, frame = cap.read()
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame = cv2.resize(frame, (resize_height, resize_width))
    i += 1
    if i == 1: # 1st frame
        print("init") # progress
        tracker.init(frame,x1,y1,width,height) # initialize CSK tracker with GT bounding box
    else: # other frames
        print("tracking") # progress
        x1, y1 = tracker.update(frame) # update CSK tracker and output estimated position
    frame = cv2.rectangle(cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR), \
                  (x1, y1), (x1 + width, y1 + height), (0, 255, 0), 2)
    cv2.imshow("cap", frame)
    if cv2.waitKey(100) & 0xff == ord('q'):
        cap.release()
        cv2.destroyAllWindows()
        break
cap.release()
cv2.destroyAllWindows()