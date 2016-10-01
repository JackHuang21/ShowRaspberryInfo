/*
 * Copyright  : 2016-2020 湖南农业大学 理学院
 * File name  : oled_gui.c
 * Description:
 *
 * Author     : Jack Huang
 * Version    : V0.1
 * Date       : Fri 03 Jun 2016 10:26:32 PM CST
 *
 * History    :
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "oled_gui.h"
#include "bsp_oled.h"
#include "data_prepare.h"

/*
 * @brief:  GUI main frame
 * @description:
 * _______________________
 *
 *         time
 * _______________________
 *
 *      information
 * _______________________
 * @param:
 * @retval:
 */
void oled_create_main_frame(void)
{
    // draw main frame
    oled_clear();
    oled_string_1206(75, 0, (uint8_t *)"CPU: ", WHITE);
    oled_string_1206(75, 13, (uint8_t *)"RAM: ", WHITE);
    oled_refresh_gram();
}




/*
 * @brief:  oled update information
 *
 * @param:
 * @retval:
 */
void gui_update_information(void)
{
    char cpu_temp[12];
    char ram_usage_rate[3];
    char system_time[40];
    oled_fill_rect(105, 127, 0, 13, BLACK);
    oled_string_1206(105, 0, (uint8_t *)get_cpu_temp(cpu_temp), WHITE);
    oled_string_1206(105, 13, (uint8_t *)get_ram_usage_rate(ram_usage_rate), WHITE);
    oled_string_1608(0, 3, (uint8_t *)get_system_time(system_time), WHITE);
}






