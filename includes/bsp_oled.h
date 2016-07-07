/**
  * Copyright  : 2015-2020 湖南农业大学 理学院
  * File name  : bsp_oled.h
  * Discription:
  *
  * Author     : Jack Huang
  * Version    : 0.1
  * Date       : May 31 2016
  *
  * History    :
  */

#ifndef __BSP_OLED_H_
#define __BSP_OLED_H_

#include <stdio.h>
#include <stdint.h>

typedef uint8_t     t_color;


// define oled_color
#define BLACK       0x00
#define WHITE       0x01




void bsp_oled_init(void);
void oled_refresh_gram(void);
void oled_on(void);
void oled_off(void);
void oled_clear(void);
void oled_draw_point(uint8_t x, uint8_t y, uint8_t state);
void oled_draw_h_line(uint8_t x_start, uint8_t x_end, uint8_t y, t_color color);
void oled_draw_v_line(uint8_t x, uint8_t y_start, uint8_t y_end, t_color color);
void oled_fill_rect(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end, t_color color);
void oled_char_1206(uint8_t x, uint8_t y, uint8_t character, t_color color);
void oled_char_1608(uint8_t x, uint8_t y, uint8_t character, t_color color);
void oled_char_2412(uint8_t x, uint8_t y, uint8_t character, t_color color);
void oled_string_1206(uint8_t x, uint8_t y, uint8_t *str, t_color color);
void oled_string_1608(uint8_t x, uint8_t y, uint8_t *str, t_color color);
void oled_string_2412(uint8_t x, uint8_t y, uint8_t *str, t_color color);
#endif






