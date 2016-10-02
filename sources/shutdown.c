#include "shutdown.h"
#include "bsp_oled.h"
#include "bsp_button.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define false       0x00
#define true        0x01


typedef uint8_t bool;


/*
 * key structure define 
 */
typedef struct key_TypeDefStructure
{
    uint16_t key_press_cnt;
    bool short_press_flag;
    bool medium_press_flag;
    bool long_press_flag;
}key_TypeDef;


key_TypeDef key_struct;     // use to save key value



/*
 * @brief:  The button value init 
 *
 * @param:  None
 * @retval: None
 */
void button_param_init(void)
{
    memset(&key_struct, 0, sizeof(key_struct));
}


/*
 * @brief:  key scan function 
 *
 * @param:  None
 * @retval: None
 */
static void _key_scan(void)
{
    if(BUTTON_INPUT == LOW)
    {
        key_struct.key_press_cnt ++;
    }
    else
    {
        if(key_struct.key_press_cnt >= 50 )
        {
            key_struct.long_press_flag = true;
        }
        else if(key_struct.key_press_cnt >= 20)
        {
            key_struct.medium_press_flag = true;
        }
        else if(key_struct.key_press_cnt >= 1)
        {
            key_struct.short_press_flag = true;
        }
        key_struct.key_press_cnt = 0;
    }
}



/*
 * @brief:  shutdown function 
 *
 * @param:  None
 * @retval: None
 */
static void _shutdown(void)
{
    static uint8_t  i = 10;
    static uint16_t cnt = 0;
    char str[20];

    memset(str, 0, sizeof(str));
    cnt ++;
    if(cnt % 10 == 0)
    {
        oled_fill_rect(0, 127, 30, 43, BLACK);
        sprintf(str, "%02ds later Poweroff!", i);
        oled_string_1206(0, 30, (uint8_t *)str, WHITE);
        if(i % 2 == 0)
        {
            LED_H;
        }
        else
        {
            LED_L;
        }
        i --;
    }
    if(key_struct.short_press_flag == true)
    {
        key_struct.short_press_flag = false;
        key_struct.medium_press_flag = false;
        cnt = 0;
        i = 10;
        LED_L;
        oled_fill_rect(0, 127, 30, 43, BLACK);
        oled_string_1206(0, 30, (uint8_t *)"Press key to poweroff", WHITE);
        return;
    }
    if(i == 0)
    {
        system("sync");
        system("sync");
        delay(200);
        system("poweroff");
    }
}



/*
 * @brief:  reboot function 
 *
 * @param:  None
 * @retval: None
 */
static void _reboot(void)
{
    static uint8_t  i = 10;
    static uint16_t cnt = 0;
    char str[20];

    memset(str, 0, sizeof(str));
    cnt ++;
    if(cnt % 10 == 0)
    {
        oled_fill_rect(0, 127, 30, 43, BLACK);
        sprintf(str, "%02ds later Reboot!", i);
        oled_string_1206(0, 30, (uint8_t *)str, WHITE);
        if(i % 2 == 0)
        {
            LED_H;
        }
        else
        {
            LED_L;
        }
        i --;
    }
    if(key_struct.short_press_flag == true)
    {
        key_struct.short_press_flag = false;
        key_struct.long_press_flag = false;
        cnt = 0;
        i = 10;
        LED_L;
        oled_fill_rect(0, 127, 30, 43, BLACK);
        oled_string_1206(0, 30, (uint8_t *)"Press key to poweroff", WHITE);
        return;
    }
    if(i == 0)
    {
        system("sync");
        system("sync");
        delay(200);
        system("reboot");
    }
}



/*
 * @brief:  system state update 
 *
 * @param:  None
 * @retval: None
 */
void system_state_refresh(void)
{
    _key_scan();
    if(key_struct.medium_press_flag == true)
    {
        _shutdown();
    }
    if(key_struct.long_press_flag == true)
    {
        _reboot();
    }
}













