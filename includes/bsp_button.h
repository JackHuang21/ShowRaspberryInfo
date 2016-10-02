#ifndef __BSP_BUTTON_H_
#define __BSP_BUTTON_H_

#define LED_H           digitalWrite(28, LOW)
#define LED_L           digitalWrite(28, HIGH)
#define BUTTON_INPUT    digitalRead(29)


void bsp_button_init(void);

#endif


