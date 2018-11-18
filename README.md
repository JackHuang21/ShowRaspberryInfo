# Show Information of Raspberry Pi

#### Description 
1. This software is base on WriringPi, so you must install wiringPi, before you use it.
2. Absolutely, you need an 0.96' oled screen, a led(low level to light led), and a button(button pull to 3.3v).
3. Hold button 2s to poweroff or hold 5s to reboot, a short press can cancle the poweroff opreation or reboot opreation. 

## Hardware Prepare
About pin number code: I use the wiringPi pin mumber code. 

Connect:
* wiringPi Pin 0  ----  oled_D0 
* wiringPi Pin 1  ----  oled_D1 
* wiringPi Pin 2  ----  oled_RES 
* wiringPi Pin 3  ----  oled_DC 
* wiringPi Pin 4  ----  oled_CS
* Board 3.3V      ----  oled_VCC
* Board GND       ----  oled_GND
* wiringPi Pin 28 ----  led
* wiringPi Pin 29 ----  button

## Install and Run
1. My Raspberry pi is Moudle 2B, it runs ubuntu mate and Raspbin, if your system is different from me, maybe this code  not work.
2. Please ensure that you have these files following: 
* /sys/class/thermal/thermal_zone0/temp  (it include TEMP information)
* /proc/meminfo  (it include RAM information)
3. If your system didn't have files above, please edit the "data_prepare.c" with the correct path.
4. If your have the same hardware and system as me, you can "cd /bin" & "sudo ./main" or you can "make" in /sources
5. If you want to run this programm when you power on, please add command to your local.rc.




