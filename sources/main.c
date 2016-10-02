/*
 * Copyright  : 2016-2020 湖南农业大学 理学院
 * File name  : main.c
 * Description:
 *
 * Author     : Jack Huang
 * Version    : V0.1
 * Date       : Wed 01 Jun 2016 12:13:41 AM CST
 *
 * History    :
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bsp_oled.h"
#include <wiringPi.h>
#include "oled_gui.h"
#include "data_prepare.h"
#include "bsp_button.h"
#include "shutdown.h"
#include <sys/time.h>
#include <signal.h>
#include <string.h>



void timeout_callback(int signal);


/**
  * @brief:  main function
  *
  * @param:  None
  * @retval: None
  */
int main(void)
{
    struct itimerval tick;
    
    memset(&tick, 0, sizeof(tick));

    // set callback function
    signal(SIGALRM, timeout_callback);

    // set timer parameters
    tick.it_value.tv_sec  = 1;
    tick.it_value.tv_usec = 0;
    tick.it_interval.tv_sec  = 0;
    tick.it_interval.tv_usec = 100000; 

    wiringPiSetup();

    // buttton and led init 
    bsp_button_init();
    // oled init
    bsp_oled_init();

    // oled_gui main frame init
    oled_create_main_frame();
    // oled refresh gram
    oled_refresh_gram();
    // button param init
    button_param_init();
    // set timer
    setitimer(ITIMER_REAL, &tick, NULL);

    while(1)
    {
        delay(200);
    }
}




/**
  * @brief:  callback function
  *
  * @param:  None
  * @retval: None
  */
void timeout_callback(int signal)
{
    static uint8_t cnt = 0;

    cnt ++;
    system_state_refresh();
    if(cnt >= 5)
    {
        gui_update_information();
        oled_refresh_gram();
        cnt = 0;
    }
}



