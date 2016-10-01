/*
 * Copyright  : 2015-2020 湖南农业大学 理学院
 * File name  : oled.c
 * Descirption:
 *
 * Author     : Jack Huang
 * Version    : 0.1
 * Date       : May 1 2016
 *
 * History    :
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bsp_oled.h"
#include "oled_font.h"
#include <wiringPi.h>

#define		OLED_D0_H	digitalWrite(0, HIGH)
#define		OLED_D1_H	digitalWrite(1, HIGH)
#define		OLED_RST_H	digitalWrite(2, HIGH)
#define		OLED_DC_H	digitalWrite(3, HIGH)
#define		OLED_CS_H	digitalWrite(4, HIGH)

#define		OLED_D0_L	digitalWrite(0, LOW)
#define		OLED_D1_L	digitalWrite(1, LOW)
#define		OLED_RST_L	digitalWrite(2, LOW)
#define		OLED_DC_L	digitalWrite(3, LOW)
#define		OLED_CS_L	digitalWrite(4, LOW)

// oled data type define
#define     OLED_CMD    0x00
#define     OLED_DATA   0x01

// oled screen size
#define     OLED_WIDTH  127
#define     OLED_HEIGHT 63



// oled frammerbuffer
uint8_t oled_gram[128][8];




/*
 * @brief:  oled write a byte
 *
 * @param:
 * @retval:
 */
static void oled_write_byte(uint8_t data, uint8_t byte_type)
{
	uint8_t i = 0;

	if(byte_type)
	{
		OLED_DC_H;
	}
	else
	{
		OLED_DC_L;
	}
	OLED_CS_L;
	for(i = 0; i < 8; i++)
	{
		OLED_D0_L;
		if(data & 0x80)
		{
			OLED_D1_H;
		}
		else
		{
			OLED_D1_L;
		}
		OLED_D0_H;
		data <<= 1;
	}
	OLED_CS_H;
	OLED_DC_H;
}



/*
 * @brief:  oled init
 *
 * @param:
 * @retval:
 */
void bsp_oled_init(void)
{
    // GPIO config
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    // reset oled
    OLED_RST_H;
    delay(200);
    OLED_RST_L;
    delay(200);
    OLED_RST_H;

    // init register
    oled_write_byte(0xAE, OLED_CMD);
    oled_write_byte(0xD5, OLED_CMD);
    oled_write_byte(0x50, OLED_CMD);
    oled_write_byte(0xA8, OLED_CMD);
    oled_write_byte(0x3F, OLED_CMD);
    oled_write_byte(0xD3, OLED_CMD);
    oled_write_byte(0x00, OLED_CMD);
    oled_write_byte(0x40, OLED_CMD);
    oled_write_byte(0x8D, OLED_CMD);
    oled_write_byte(0x14, OLED_CMD);
    oled_write_byte(0x20, OLED_CMD);
    oled_write_byte(0x02, OLED_CMD);
    oled_write_byte(0xA1, OLED_CMD);
    oled_write_byte(0xC0, OLED_CMD);
    oled_write_byte(0xDA, OLED_CMD);
    oled_write_byte(0x12, OLED_CMD);
    oled_write_byte(0x81, OLED_CMD);
    oled_write_byte(0xEF, OLED_CMD);
    oled_write_byte(0xD9, OLED_CMD);
    oled_write_byte(0xF1, OLED_CMD);
    oled_write_byte(0xDB, OLED_CMD);
    oled_write_byte(0x30, OLED_CMD);
    oled_write_byte(0xA4, OLED_CMD);
    oled_write_byte(0xA6, OLED_CMD);
    oled_write_byte(0xAF, OLED_CMD);

    oled_clear();
    oled_refresh_gram();
}


/*
 * @brief:  oled refresh gram
 *
 * @param:
 * @retval:
 */
void oled_refresh_gram(void)
{
    uint8_t i = 0;
    uint8_t j = 0;

    for(i = 0; i < 8; i++)
    {
        oled_write_byte(0xB0 + i, OLED_CMD);
        oled_write_byte(0x00, OLED_CMD);
        oled_write_byte(0x10, OLED_CMD);
        for(j = 0; j < 128; j++)
        {
            oled_write_byte(oled_gram[j][i], OLED_DATA);
        }
    }
}




/************************************************ OLED  BASIC FUNCTIONS **********************************************/

/*
 * @brief:  oled on
 *
 * @param:
 * @retval:
 */
void oled_on(void)
{
    oled_write_byte(0x8D, OLED_CMD);
    oled_write_byte(0x14, OLED_CMD);
    oled_write_byte(0xAF, OLED_CMD);
}


/*
 * @brief: oled off
 *
 * @param:
 * @retval:
 */
void oled_off(void)
{
    oled_write_byte(0x8D, OLED_CMD);
    oled_write_byte(0x10, OLED_CMD);
    oled_write_byte(0xAE, OLED_CMD);

}


/*
 * @brief:  oled clear
 *
 * @param:
 * @retval:
 */
void oled_clear(void)
{
    uint8_t i = 0;
    uint8_t j = 0;

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 128; j++)
        {
            oled_gram[j][i] = 0x00;
        }
    }
    oled_refresh_gram();
}


/*
 * @brief:  oled draw point
 *
 * @param:
 * @retval:
 */
void oled_draw_point(uint8_t x, uint8_t y, t_color color)
{
    uint8_t pos_y = 0;
    uint8_t temp  = 0;
    uint8_t bit_x = 0;

    assert(x < 128 && x >= 0);
    assert(y < 64 && y >= 0);

    pos_y = 7 - y / 8;
    bit_x =  y % 8;
    temp = 1 << (7 - bit_x);

    if(color)
    {
        oled_gram[x][pos_y] |= temp;
    }
    else
    {
        oled_gram[x][pos_y] &= ~temp;
    }
}



/*
 * @brief:  oled draw h line
 *
 * @param:
 * @retval:
 */
void oled_draw_h_line(uint8_t x_start, uint8_t x_end, uint8_t y, t_color color)
{
    uint8_t i = 0;
    // check param
    assert(x_start >= 0 && x_start < 128);
    assert(x_end >x_start && x_end < 128);
    assert(y >= 0 && y < 64);
    assert(color == 0x01 || color == 0x00);

    for(i = x_start; i < x_end; i++)
    {
        oled_draw_point(i, y, color);
    }
}


/*
 * @brief:  oled draw v line
 *
 * @param:
 * @retval:
 */
void oled_draw_v_line(uint8_t x, uint8_t y_start, uint8_t y_end, t_color color)
{
    uint8_t i = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y_start >= 0 && y_start < 64);
    assert(y_end > y_start && y_end < 64);
    assert(color == 0x00 || color == 0x01);

    for(i = y_start; i < y_end; i++)
    {
        oled_draw_point(x, i, color);
    }
}



/*
 * @brief:  oled fill rectangle
 *
 * @param:
 * @retval:
 */
void oled_fill_rect(uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end, t_color color)
{
    uint8_t i = 0;
    uint8_t j = 0;

    // check param
    assert(x_start >= 0 && x_start < 128);
    assert(x_end > x_start && x_end < 128);
    assert(y_start >= 0 && y_start < 64);
    assert(y_end > y_start && y_end < 64);
    assert(color == 0x01 || color == 0x00);

    for(i = x_start; i < x_end; i ++)
    {
        for(j = y_start; j < y_end; j++)
        {
            oled_draw_point(i, j, color);
        }
    }
}



/*
 * @brief:  oled display a char that size is 1206
 *
 * @param:
 * @retval:
 */
void oled_char_1206(uint8_t x, uint8_t y, uint8_t character, t_color color)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;
    uint8_t temp  = 0;
    uint8_t character_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);

    x_pos = x;
    y_pos = y;
    character_pos = character - ' ';

    for(i = 0; i < 12; i++)
    {
        // get the font data
        temp = asc2_1206[character_pos][i];
        for(j = 0; j < 8; j++)
        {
            if(temp & 0x80)
            {
                oled_draw_point(x_pos, y_pos, color);
            }
            else
            {
                oled_draw_point(x_pos, y_pos, !color);
            }
            temp <<= 1;
            y_pos ++;
            if((y_pos - y) == 12)
            {
                y_pos = y;
                x_pos ++;
                break;
            }
        }
    }
}



/*
 * @brief:  oled display a char that size is 1608
 *
 * @param:
 * @retval:
 */
void oled_char_1608(uint8_t x, uint8_t y, uint8_t character, t_color color)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;
    uint8_t temp  = 0;
    uint8_t character_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);

    x_pos = x;
    y_pos = y;
    character_pos = character - ' ';

    for(i = 0; i < 16; i++)
    {
        // get the font data
        temp = asc2_1608[character_pos][i];
        for(j = 0; j < 8; j++)
        {
            if(temp & 0x80)
            {
                oled_draw_point(x_pos, y_pos, color);
            }
            else
            {
                oled_draw_point(x_pos, y_pos, !color);
            }
            temp <<= 1;
            y_pos ++;
            if((y_pos - y) == 16)
            {
                y_pos = y;
                x_pos ++;
                break;
            }
        }
    }
}




/*
 * @brief:  oled display a char that size is 2412
 *
 * @param:
 * @retval:
 */
void oled_char_2412(uint8_t x, uint8_t y, uint8_t character, t_color color)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;
    uint8_t temp  = 0;
    uint8_t character_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);

    x_pos = x;
    y_pos = y;
    character_pos = character - ' ';

    for(i = 0; i < 36; i++)
    {
        // get the font data
        temp = asc2_2412[character_pos][i];
        for(j = 0; j < 8; j++)
        {
            if(temp & 0x80)
            {
                oled_draw_point(x_pos, y_pos, color);
            }
            else
            {
                oled_draw_point(x_pos, y_pos, !color);
            }
            temp <<= 1;
            y_pos ++;
            if((y_pos - y) == 24)
            {
                y_pos = y;
                x_pos ++;
                break;
            }
        }
    }
}



/*
 * @brief:  oled show string 1206
 *
 * @param:
 * @retval:
 */
void oled_string_1206(uint8_t x, uint8_t y, uint8_t *p_str, t_color color)
{
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);
    x_pos = x;
    y_pos = y;

    while( (*p_str <= '~') && (*p_str >= ' ') )
    {
        if( x_pos > 122)
        {
            x_pos = 0;
            y_pos += 12;
        }

        if(y > 54)
        {
            y_pos = 0;
            x_pos = 0;
            oled_clear();
        }
        oled_char_1206(x, y, *p_str, color);
        x += 6;
        p_str ++;
    }
}


/*
 * @brief:  oled show string 1206
 *
 * @param:
 * @retval:
 */
void oled_string_1608(uint8_t x, uint8_t y, uint8_t *p_str, t_color color)
{
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);
    x_pos = x;
    y_pos = y;

    while( (*p_str <= '~') && (*p_str >= ' ') )
    {
        if( x_pos > 120)
        {
            x_pos = 0;
            y_pos += 16;
        }

        if(y > 52)
        {
            y_pos = 0;
            x_pos = 0;
            oled_clear();
        }
        oled_char_1608(x, y, *p_str, color);
        x += 8;
        p_str ++;
    }
}



/*
 * @brief:  oled show string 1206
 *
 * @param:
 * @retval:
 */
void oled_string_2412(uint8_t x, uint8_t y, uint8_t *p_str, t_color color)
{
    uint8_t x_pos = 0;
    uint8_t y_pos = 0;

    // check param
    assert(x >= 0 && x < 128);
    assert(y >= 0 && y < 64);
    x_pos = x;
    y_pos = y;

    while( (*p_str <= '~') && (*p_str >= ' ') )
    {
        if( x_pos > 116)
        {
            x_pos = 0;
            y_pos += 12;
        }

        if(y > 40)
        {
            y_pos = 0;
            x_pos = 0;
            oled_clear();
        }
        oled_char_2412(x, y, *p_str, color);
        x += 12;
        p_str ++;
    }

}



















