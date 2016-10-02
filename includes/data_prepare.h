/*
 * Copyright  : 2016-2020 湖南农业大学 理学院
 * File name  : ../includes/data_prepare.h
 * Description:
 *
 * Author     : Jack Huang
 * Version    : V0.1
 * Date       : Fri 03 Jun 2016 11:05:09 PM CST
 *
 * History    :
 */
#ifndef __DATA_PREPARE_H_
#define __DATA_PREPARE_H_

#include <stdint.h>

char *get_cpu_temp(char *p_str);
char *get_ram_usage_rate(char *p_str);
char *get_weather_info(char *p_str);
char *get_system_time(char *p_str);
char *get_system_ip_address(char *p_str);

#endif



