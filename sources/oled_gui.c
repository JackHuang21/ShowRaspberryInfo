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
#include <string.h>
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
    oled_string_1206(0, 52, (uint8_t *)"Press key to poweroff", WHITE);
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
    char temp_str[48];
    char ip_addr[3][21];
    static uint16_t cnt = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    
    memset(ram_usage_rate, 0, sizeof(ram_usage_rate));
    memset(system_time, 0, sizeof(system_time));
    oled_fill_rect(105, 127, 0, 13, BLACK);
    oled_string_1206(105, 0, (uint8_t *)get_cpu_temp(cpu_temp), WHITE);
    oled_string_1206(105, 13, (uint8_t *)get_ram_usage_rate(ram_usage_rate), WHITE);
    oled_string_1608(0, 3, (uint8_t *)get_system_time(system_time), WHITE);
    if( (cnt >= 60) || (cnt == 0) )
    {
        memset(temp_str, 0, sizeof(temp_str));
        for(i = 0; i < 3; i++)
        {
            memset(ip_addr[i], 0, sizeof(ip_addr[i]));
        }
        get_system_ip_address(temp_str);
        i = 0;
        while(temp_str[i] != '\0')
        {
            if(temp_str[i] != '#')
            {
                ip_addr[j][k] = temp_str[i];
                k ++;
            }
            else
            {
                j ++;
                k = 0;
            }
            i ++;
        }
        // display eth0 ip address
        oled_fill_rect(0, 127, 25, 49, BLACK);
        if(strlen(ip_addr[0]) < 10)
        {
            oled_string_1206(0, 25, (uint8_t *)"N/A", WHITE);
        }
        else
        {
            oled_string_1206(0, 25, (uint8_t *)ip_addr[0], WHITE);
        }
        // display wlan ip address
        if(strlen(ip_addr[1]) < 10)
        {
            oled_string_1206(0, 37, (uint8_t *)"N/A", WHITE);
        }
        else
        {
            oled_string_1206(0, 37, (uint8_t *)ip_addr[1], WHITE);
        }
        cnt = 0;
    }
    cnt ++;
}






