#include "bsp_button.h"
#include <wiringPi.h>


/*
 * @brief:  The button and led gpio config
 *
 * @param:  None
 * @retval: None
 */
void bsp_button_init(void)
{
    pinMode(28, OUTPUT);
    pinMode(29, INPUT);
    LED_H;    
}




