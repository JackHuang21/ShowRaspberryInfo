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



int main(void)
{
    wiringPiSetup();
    bsp_oled_init();

    // oled_gui main frame init
    oled_create_main_frame();
    // oled refresh gram
    oled_refresh_gram();

    while(1)
    {
        delay(500);
        gui_update_information();
        oled_refresh_gram();
        delay(500);
    }
}







