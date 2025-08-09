/*
 * @file         : 
 * @Author       : shuyu
 * @LastEditTime : 2025-08-09 20:36
 * @Description  : 
 */

#include "lcd_ui.h"
#include "font.h"


static LCD_DRIVER ui_driver;
static PAINT paint;

static uint8_t img_bw[2888];


/**
 * @funciton:   ui_clear
 * @brief:      擦除屏幕
 */
void ui_clear(void) {
    ui_driver.clear();
}

/**
 * @function:       ui_buf_claer
 * @breif:          清空缓冲数组
 * @param{color}    颜色
 * @retval:         NULL
 */
void ui_buf_clear(uint8_t Color) {
  uint16_t x,y;
  uint32_t addr;
  for(y = 0;y < paint.heightByte; y++) 
  {
    for(x=0;x < paint.widthByte; x++ ) 
    {   
      addr = x + (y * paint.widthByte);         //8 pixel =  1 byte
      paint.dis_buffer[addr] = Color;
    }
  }
}

/**
 * @function:       ui_new_img
 * @brief:          创建一个画布
 * @param{image}    传入的缓冲区
 * @param{width}    创建的大小
 * @param{height}   创建的大小
 * @param{rotate}   方向
 * @param{color}    颜色
 */
static void ui_new_img(uint8_t *image,uint16_t Width,uint16_t Height,uint16_t Rotate,uint16_t Color)
{
  paint.dis_buffer = 0x00;
  paint.dis_buffer = image;
  paint.color = Color;  
  paint.widthMemory = Width;
  paint.heightMemory = Height;  
  paint.widthByte = (Width % 8 == 0)? (Width / 8 ): (Width / 8 + 1);
  paint.heightByte = Height;     
  paint.rotate = Rotate;
  if((Rotate == 0) || (Rotate == 180)) {
    paint.width=Height;
    paint.height=Width;
  }else {
    paint.width = Width;
    paint.height = Height;
  }

  ui_buf_clear(WHITE);
}   



/**
 * @funciton:       ui_set_pixel
 * @breif:          显示一个像素点
 * @param{xpoint}   x的起始地址
 * @param{ypoint}   y的起始地址
 * @param{color}    颜色
 */

static void ui_set_pixel(uint16_t xpoint,uint16_t ypoint,uint16_t color) {
    uint16_t x, y;
    uint32_t addr;
    uint8_t r_data;
        switch(paint.rotate) {
        case 0:
            x = xpoint;
            y = paint.heightMemory - ypoint - 1;    
            break;
        case 90:
            x = paint.widthMemory - ypoint - 1;
            y = paint.heightMemory - xpoint - 1;
            break;
        case 180:
            x = paint.widthMemory - xpoint - 1;
            y = ypoint;
            break;
        case 270:
            x = ypoint;
            y = xpoint;
            break;
            default:
                return;
        }
        addr = (x / 8) + (y * paint.widthByte);
        r_data = paint.dis_buffer[addr];
        if(color == BLACK) {    
            paint.dis_buffer[addr] = r_data & ~(0x80>>(x % 8)); //将对应数据位置0
        }
        else{
            paint.dis_buffer[addr] = r_data | (0x80>>(x % 8));   //将对应数据位置1  
        }
 }


/**
 * @function:   ui_init
 * @brief:      用户使用接口ui初始化
 * @param{NULL} NULL
 */
void ui_init(void) {
    ssd1680_driver_init_callback(&ui_driver);
    ui_driver.ui_init();
    ui_new_img(img_bw,LCD_WIDTH,LCD_HEIGHT,0,WHITE);
} 


/**
 * @funciton:       ui_disp
 * @brief:          显示
 * @param{buf}:     需要显示的缓冲区
 * @retval:         NULL
 */

void ui_disp(const uint8_t* buf) {
    ui_driver.disp(buf);
}

/**
 * @function:   ui_updata
 * @brief:      更新
 * @param{NULL} NULL
 * @retval:     NULL
 */
void ui_updata(void) {
    ui_driver.update();
}


/**
 * @function:   ui_show_char
 * @brief:      打印一个字符
 * @param{x}    x起始地址
 * @param{y}    y起始地址
 * @param{chr}  传入的字符
 * @param{size1}字体的大小
 * @param{color}字体的颜色
 * @retval:     NULL
 */

void ui_show_char(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1,uint16_t color)
{
  uint16_t i,m,temp,size2,chr1;
  uint16_t x0,y0;
  x0 = x;
  y0 = y;
  if(size1 == 8) {
    size2 = 6;
  }else{
    size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2);  //得到字体一个字符对应点阵集所占的字节数
  } 
  chr1 = chr - ' ';  //计算偏移后的值
  for(i = 0;i < size2;i++)
  {
    if(size1 == 8)
        {temp = asc2_0806[chr1][i];} //调用0806字体
    else if(size1 == 12)
        {temp = asc2_1206[chr1][i];} //调用1206字体
    else if(size1 == 16)
        {temp = asc2_1608[chr1][i];} //调用1608字体
    else if(size1 == 24)
        {temp = asc2_2412[chr1][i];} //调用2412字体
    else if(size1 == 48)
        {temp = asc2_4824[chr1][i];} //调用2412字体
    else return;
    for(m = 0; m < 8; m++)
    {
      if(temp & 0x01){
        ui_set_pixel(x,y,color);
      } else {
        ui_set_pixel(x,y,!color);
      }
      temp >>= 1;
      y++;
    }
    x++;
    if((size1 != 8) && ((x - x0) == size1 / 2)){
        x = x0;
        y0 = y0+8;
    }
    y = y0;
  }

}



/**
 * @function:   ui_show_string
 * @brief:      显示字符串
 * @param{x}    起始x
 * @param{y}    起始y
 * @param{chr}  显示的字符串
 * @param{size} 显示的大小
 * @param{color} 显示的颜色
 */
void ui_show_string(uint16_t x,uint16_t y,uint8_t* chr,uint16_t size1,uint16_t color) {
    while(*chr!='\0') {
        ui_show_char(x,y,*chr,size1,color);
        chr++;
        x += size1 / 2;
    }
    ui_disp(img_bw);
    ui_updata();
}


/**
 * @function:	ui_show_picture
 * @brief:      显示图片
 * @param{x}    起始X坐标
 * @param{y}    起始Y坐标
 * @param{sizex} X长度
 * @param{sizey} Y长度
 * @param{BMP[]} 传入的缓冲数组    
 */

void ui_show_picture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t* BMP,uint16_t Color)
{
  uint16_t j=0,t;
  uint16_t i,temp,y0,TypefaceNum=sizex*(sizey/8+((sizey%8)?1:0));
  y0=y;
  for(i=0;i<TypefaceNum;i++)
  {
    temp=BMP[j];
    for(t=0;t<8;t++)
    {
     if(temp&0x80)
     {
       ui_set_pixel(x,y,Color);
     }
     else
     {
       ui_set_pixel(x,y,!Color);
     }
     y++;
     temp<<=1;
    }
    if((y-y0)==sizey)
    {
      y=y0;
      x++;
    }
    j++;
  }

  ui_disp(img_bw);
  ui_updata();
}




/**
 * @function:   ui_sleep
 * @brief:      支持睡眠的低功耗屏
 * @param{NULL} NULL
 */
void ui_sleep(void) {
    ui_driver.sleep();
}


