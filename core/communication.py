import serial
import sys
sys.path.append('../CSK')
import cv2
import csk
from csk import *
import time

ori_width = 1280
ori_height = 720
resize_width = 320
resize_height = 180
tracker = csk.CSK() # CSK instpance
# cap = cv2.VideoCapture(0)
cap = cv2.VideoCapture(1)


# ser = serial.Serial("/dev/ttyACM0", 9600, timeout=0.5)
ser = serial.Serial("/dev/cu.usbmodem141101", 9600, timeout=0.06)



def getInitPos():
	bias = 20
	x1 = int(426 * (resize_width / ori_width)) # position x of the top-left corner of bounding box
	y1 = int(bias * (resize_height / ori_height))
	width = int(426 * (resize_width / ori_width)) # the width of bounding box
	height = ori_height - bias - y1
	if height < 0:
		height += bias
	height = int(height * (resize_height / ori_height))
	return x1, y1, width, height

# def getAngleBias(x, ori_x, ori_w):
# 	return max(0, min(255,int((ori_x - x) / ori_w * 127) + 128))

def getAngleBias(x, ori_x, ori_w, pre_angle):
	cur_angle = max(0, min(255,int((ori_x - x) / ori_w * 127) + 128))
	if cur_angle - pre_angle > 10:
		cur_angle = 5 + pre_angle
	elif cur_angle - pre_angle < -10:
		cur_angle = -5 + pre_angle
	else:
		cur_angle = pre_angle
	return cur_angle

def smooth(x, hist):
	beta = 0.5
	x = int(hist * beta + x * (1-beta))
	return x



# try:
ori_x, ori_y, ori_w, ori_h = getInitPos()
x, y = ori_x, ori_y
i = 0
ori_dist = 500
hist_box = ()
hist_angle = 128
pre_angle = 128
while 1:
	# ser.write('s')
	response = ser.readline()
	if response:
		response = bytes.decode(response).strip()
	if response and response.startswith("distance="):
		dist = int(response.split('=')[-1])
		i += 1
		ret, frame = cap.read()
		frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		frame = cv2.resize(frame, (resize_width, resize_height))
		if i == 1:
			print("init")  # progress
			tracker.init(frame, ori_x, ori_y, ori_w, ori_h)  # initialize CSK tracker with GT bounding box
			hist_box = (ori_x, ori_y)
		else:  # other frames
			print("tracking")  # progress
			x, y = tracker.update(frame)  # update CSK tracker and output estimated position
			x, y = smooth(x, hist_box[0]), smooth(y, hist_box[1])
			hist_box = (x, y)
		frame = cv2.rectangle(cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR), \
							  (x, y), (x + ori_w, y + ori_h), (0, 255, 0), 2)
		cv2.imshow("cap", frame)
		if cv2.waitKey(100) & 0xff == ord('q'):
			cap.release()
			cv2.destroyAllWindows()
			out = 'm'
			ser.write(out.encode('utf8'))
			break
		x_bias = x - ori_x
		y_bias = y - ori_y
		dist_bias = dist - ori_dist
		angle_bias = getAngleBias(x, ori_x, ori_w, pre_angle)

		# angle_bias = smooth(angle_bias, hist_angle)
		# hist_angle = angle_bias
		# print(x, ori_x)
		print(angle_bias)
		# if abs(angle_bias - pre_angle) > 10:
		out = 'a{}'.format(chr(angle_bias))
		ser.write(out.encode('utf8'))
		pre_angle = angle_bias
# except:
# 	print("Error!")
# 	ser.close()
	
