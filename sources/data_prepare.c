/*
 * Copyright  : 2016-2020 湖南农业大学 理学院
 * File name  : data_prepare.c
 * Description:
 *
 * Author     : Jack Huang
 * Version    : V0.1
 * Date       : Fri 03 Jun 2016 11:04:27 PM CST
 *
 * History    :
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include "data_prepare.h"


#define TEMP_PATH       "/sys/class/thermal/thermal_zone0/temp"
#define RAM_PATH        "/proc/meminfo"
#define WEATHER_PATH    "/home/jack/Data/weather_data.txt"
#define TEMP_SIZE       32



/*
 * @brief:  oled get cpu temp
 *
 * @param:
 * @retval:
 */
char *get_cpu_temp(char *p_str)
{
    FILE *p_read_file = NULL;
    uint8_t cpu_temp = 0;

    p_read_file = fopen(TEMP_PATH, "r");
    assert(p_read_file != NULL);
    fread(p_str, sizeof(char), 10, p_read_file);
    fclose(p_read_file);
    cpu_temp = atoi(p_str) / 1000;
    sprintf(p_str, "%dC", cpu_temp);
    return p_str;
}


/*
 * @brief:  get ram info
 *
 * @param:
 * @retval:
 */
char * get_ram_usage_rate(char *p_str)
{
    FILE *p_read_file = NULL;
    char     ram_total_str[6];
    char     ram_free_str[6];
    uint32_t ram_total_number = 0;
    uint32_t ram_free_number   = 0;
    uint8_t  ram_usage_rate = 0;

    // open the file, get the data
    p_read_file = fopen(RAM_PATH, "r");
    assert(p_read_file != NULL);
    fseek(p_read_file, 18, SEEK_SET);
    fread(ram_total_str, sizeof(char), 6, p_read_file);
    fseek(p_read_file, 50, SEEK_CUR);
    fread(ram_free_str, sizeof(char), 6, p_read_file);
    fclose(p_read_file);
    // change format
    ram_total_number = atoi(ram_total_str);
    ram_free_number   = atoi(ram_free_str);
    ram_usage_rate = (ram_total_number - ram_free_number) * 100 / ram_total_number;
    sprintf(p_str, "%d%%", ram_usage_rate);
    return p_str;
}


/*
 * @brief:  get weather info
 *
 * @param:
 * @retval:
 */
char *get_weather_info(char *p_str)
{
    FILE *p_read_file = NULL;
    char weather_info_str[20];

    // open file and read it
    p_read_file = fopen(WEATHER_PATH, "r");
    assert(p_read_file != NULL);
    fseek(p_read_file, 59, SEEK_SET);
    fread(weather_info_str, sizeof(char), 20, p_read_file);
    fclose(p_read_file);

    // handle data
    printf("%s\n", weather_info_str);
    return NULL;
}





/*
 * @brief:  get system time
 *
 * @param:
 * @retval:
 */
char *get_system_time(char *p_str)
{
    time_t local_time;
    struct tm *nowtime;

    time(&local_time);
    nowtime = localtime(&local_time);
    strftime(p_str, 40, "%Y-%m-%d %H:%M:%S", nowtime);
    return p_str + 11;
}


/*
 * @brief:  get all ip address
 *
 * @param:
 * @retval:
 */
char *get_system_ip_address(char *p_str)
{
    struct ifaddrs *ifaddr_structure = NULL; 
    void *temp_addr_bin_str = NULL;
    char temp_ip_dec_str[16];
    uint8_t n = 0;

    memset(temp_ip_dec_str, 0, sizeof(temp_ip_dec_str));
    getifaddrs(&ifaddr_structure);  // 获取本机接口信息
    while(ifaddr_structure != NULL)
    {
        if(ifaddr_structure->ifa_addr->sa_family == AF_INET) // 仅返回IPV4地址
        {
            temp_addr_bin_str = &((struct sockaddr_in *)ifaddr_structure->ifa_addr)->sin_addr; // sin_addr存储了IP地址
            inet_ntop(AF_INET, temp_addr_bin_str, temp_ip_dec_str, 16);  // 二进制转点分十进制
            if(strcmp(temp_ip_dec_str, "127.0.0.1") != 0)
            {
                strncat(p_str, ifaddr_structure->ifa_name, 4);
                strncat(p_str, ":", 1);
                if(n == 0)
                {
                    strncat(p_str, temp_ip_dec_str, 16);
                    strncat(p_str, "#", 1);
                }
                else
                {
                    strncat(p_str, temp_ip_dec_str, 16);
                    strncat(p_str, "#", 1);
                }
                n++;
            }
        }
        ifaddr_structure = ifaddr_structure->ifa_next;
    }
    freeifaddrs(ifaddr_structure);
    return p_str;
}




