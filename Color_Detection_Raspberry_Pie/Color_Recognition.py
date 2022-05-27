# Reference: https://www.electronicshub.org/raspberry-pi-color-sensor-tutorial/

import RPi.GPIO as GPIO
import time



s2 = 23		   # S2 pin of the sensor connected to GPIO23 of Raspberry Pi
s3 = 24		   # S3 pin of the sensor connected to GPIO24 of Raspberry Pi
signal = 25	   # OUT signal connected to GPIO25 of Raspberry Pi
NUM_CYCLES = 10

GPIO.setwarnings(False)


def setup():
  GPIO.setmode(GPIO.BCM)
  GPIO.setup(signal,GPIO.IN, pull_up_down=GPIO.PUD_UP)
  GPIO.setup(s2,GPIO.OUT)
  GPIO.setup(s3,GPIO.OUT)
  print("\n")
  




def loop():
  temp = 1
  while(1):  

    GPIO.output(s2,GPIO.LOW)
    GPIO.output(s3,GPIO.LOW)
    time.sleep(0.3)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start 
    red  = NUM_CYCLES / duration   
   
    GPIO.output(s2,GPIO.LOW)
    GPIO.output(s3,GPIO.HIGH)
    time.sleep(0.3)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start
    blue = NUM_CYCLES / duration
    

    GPIO.output(s2,GPIO.HIGH)
    GPIO.output(s3,GPIO.HIGH)
    time.sleep(0.3)
    start = time.time()
    for impulse_count in range(NUM_CYCLES):
      GPIO.wait_for_edge(signal, GPIO.FALLING)
    duration = time.time() - start
    green = NUM_CYCLES / duration
    
          
    if green<17000 and blue<20000 and red>22000:
      print("red")
      temp=1
    elif red<16000 and  blue<16000 and green>18000:
      print("green")
      temp=1
    elif green<19000 and red<19000 and blue>19000:
      print("blue")
      temp=1
    elif green<12000 and red<12000 and blue<10000:
      print("black")
      temp=1
    elif green>20000 and red>20000 and blue>22000:
      print("white")
      temp=1
    elif green<20000 and red>22000 and blue<22000:
      print("orange")
      temp=1
    elif green<19000 and red>22000 and blue<24000:
      print("pink")
      temp=1
    elif red>10000 and green<14000 and blue<16000 and temp==1:
      print("place the object.....")
      temp=0


def endprogram():
    GPIO.cleanup()

if __name__=='__main__':
    
    setup()

    try:
        loop()

    except KeyboardInterrupt:
        endprogram()