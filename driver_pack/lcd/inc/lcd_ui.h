/*
 * @file         : 
 * @Author       : shuyu
 * @LastEditTime : 2025-08-09 19:52
 * @Description  : 
 */

 #ifndef LCD_UI_H__
 #define LCD_UI_H__


#include "epd.h"

#define BLACK       0xFF
#define WHITE       0x00

typedef struct {
	uint8_t *dis_buffer;
	uint16_t width;
	uint16_t height;
	uint16_t widthMemory;
	uint16_t heightMemory;
	uint16_t color;
	uint16_t rotate;        //显示方向
	uint16_t widthByte;
	uint16_t heightByte;
}PAINT;


void ui_init(void);
void ui_disp(const uint8_t* buf);
void ui_updata(void);
void ui_show_char(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1,uint16_t color);
void ui_show_string(uint16_t x,uint16_t y,uint8_t* chr,uint16_t size1,uint16_t color);
void ui_show_picture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t* BMP,uint16_t Color);
void ui_buf_clear(u8 Color);
void ui_sleep(void);
void ui_clear(void);


#endif
