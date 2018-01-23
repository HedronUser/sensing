import serial
import time
import os

ser = serial.Serial('/dev/tty.usbmodem3352381', 9600)
now = int(time.time())

with open("%s.RAW" %(now), "w") as f:
    hadData = False;
    print("recording...")
    while 1:
        if ser.in_waiting > 0:
            if hadData == False:
                print("recording finished! receiving data")
                hadData = True
        if hadData and ser.in_waiting == 0:
            print("done receiving data")
            break
        else:
            data = ser.read()
            f.write(data)
    f.close()
    print("converting file...")
    os.system("./rawToWav.sh %s" %(now))
    print("%s.wav saved to disc." %(now))
