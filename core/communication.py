import serial
ser = serial.Serial("/dev/ttyACM0", 9600, timeout=0.5)
try:
	while 1:
		# ser.write('s')
		response = ser.read()
		print(response)
except:
	print("Error!")
	ser.close()
	
