# Show Information of Raspberry Pi #
Exactly, this is my first github repository~

####Description##
1. This software is base on WriringPi, so you must install wiringPi, before you use it.
2. Absolutely, you need an 0.96' oled screen.

##Hardware Prepare##
About pin number code: I use the wiringPi pin mumber code. 

Connect:
* wiringPi Pin 0  ----  oled_D0 
* wiringPi Pin 1  ----  oled_D1 
* wiringPi Pin 2  ----  oled_RES 
* wiringPi Pin 3  ----  oled_DC 
* wiringPi Pin 4  ----  oled_CS
* Board 3.3V      ----  oled_VCC
* Board GND       ----  oled_GND

##Install and Run
1. My raspberry pi is Moudle 2B, it runs ubuntu mate, if your system is different from me, maybe this code  not work.
2. Please ensure that you have these files following: 
* /sys/class/thermal/thermal_zone0/temp  (is include TEMP information)
* /proc/meminfo  (it include RAM information)
3. If your system didn't have files above, please edit the data_prepare.c with the correct path.
4. If your have the same hardware and system as me, you can "cd bin" & "./main"
5. If you want to run this programm when you power on, please add command to your local.rc.




