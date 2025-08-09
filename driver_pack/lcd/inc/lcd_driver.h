#ifndef LCD_DRIVER_H__
#define LCD_DRIVER_H__


#include "sc_conf.h"

typedef struct {
    void(*spi_init)(void);                  /**SPI初始化函数 */
    uint8_t(*spi_transbyte)(uint8_t);       /**SPI发送一个字节接收一个字节*/
    void(*set_cs)(uint8_t);                 /**设置cs片选*/
    void(*set_dc)(uint8_t);                 /**设置命令数据*/
}SPI_DEV;

typedef struct {
    void(*ui_init)(void);               // 初始化函数
    void(*disp)(const uint8_t*);        // 显示函数
    void(*update)(void);                // 更新函数
    void(*clear)(void);                 // 擦屏函数
    void(*sleep)(void);                 // 支持低功耗的屏幕（可选）
}LCD_DRIVER;


/*SSD1680   屏幕驱动 */
#if SSD1680_ENABLE
typedef struct {
    SPI_DEV*  dev;
    void(*write_cmd)(uint8_t);
    void(*write_data)(uint8_t);
    uint8_t(*read_busy)(void);
    void(*set_reset)(uint8_t);
}SSD1680_SPI;

void lcd_fn_register(SSD1680_SPI* lcd_dev);

#endif

#endif
