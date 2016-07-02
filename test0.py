import pyupm_i2clcd as lcd
import time

while True:
    myLcd = lcd.Jhd1313m1(0, 0x3E, 0x62)
    var = raw_input("Red, Green or Blue?")
    if(var == "Red"):
        myLcd.setColor(255, 0, 0)
        myLcd.write("You Choose Red")
    elif(var == "Green"):
        myLcd.setColor(0, 255, 0)
    elif(var == "Blue"):
        myLcd.setColor(0, 0, 255)
    else:        
        print "Not A Choice!!"
    time.sleep(2)

