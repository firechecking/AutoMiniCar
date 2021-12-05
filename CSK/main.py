import csk
from csk import *
import numpy as np
# from scipy.misc.pilutil import imread, imsave
from imageio import imread, imsave
import cv2 # (Optional) OpenCV for drawing bounding boxes


# 1st frame's groundtruth information
# for my_pic
length = 3 # sequence length
x1 = 260 # position x of the top-left corner of bounding box
y1 = 20 # position y of the top-left corner of bounding box
width = 284 # the width of bounding box
height = 410 # the height of bounding box

# for my_pic2
length = 32 # sequence length
x1 = 160 # position x of the top-left corner of bounding box
y1 = 290 # position y of the top-left corner of bounding box
width = 220 # the width of bounding box
height = 220 # the height of bounding box

sequence_path = "/Users/xuming.lxm/Workplace/CSK/my_pic2/" # your sequence path
save_path = "/Users/xuming.lxm/Workplace/CSK/my_pic2/" # your save path

tracker = csk.CSK() # CSK instpance

for i in range(1,length+1): # repeat for all frames
    frame = imread(sequence_path+"p%d.jpg"%i, as_gray=True)
    # imsave(save_path+'%d.jpg'%i,cv2.rectangle(cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR), \
    #     (x1, y1), (x1+width, y1+height), (0,255,0), 2))

    if i == 1: # 1st frame
        print(str(i)+"/"+str(length)) # progress
        tracker.init(frame,x1,y1,width,height) # initialize CSK tracker with GT bounding box
        imsave(save_path+'%d.jpg'%i,cv2.rectangle(cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR), \
        (x1, y1), (x1+width, y1+height), (0,255,0), 2)) # draw bounding box and save the frame

    else: # other frames
        print(str(i)+"/"+str(length)) # progress
        x1, y1 = tracker.update(frame) # update CSK tracker and output estimated position
        imsave(save_path+'%d.jpg'%i,cv2.rectangle(cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR), \
        (x1, y1), (x1+width, y1+height), (0,255,0), 2)) # draw bounding box and save the frame