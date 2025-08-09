/*
 * @file         : lcd_driver.c
 * @Author       : shuyu
 * @LastEditTime : 2025-08-09 17:09
 * @Description  : lcd_driver的驱动文件
 */
#include "lcd_driver.h"

// TODO:目前无法支持多个SPI—LCD设备
static SPI_DEV spi_dev = {
    .spi_init = SPI_INIT,
    .spi_transbyte = SPI_SWAP_BYTE,
    .set_cs = SPI_SET_CS,
    .set_dc = SPI_SET_DC
};

/**
 * @fuunciton:      spi_write_reg
 * @brief:          写命令函数
 * @param{data}:    写入的命令数据
 * @retval:         NULL
 */
static void spi_write_cmd(uint8_t cmd) {
    spi_dev.set_dc(0);
    spi_dev.set_cs(0);
    spi_dev.spi_transbyte(cmd);
    spi_dev.set_cs(1);
    spi_dev.set_dc(1);
}

/**
 * @fuunciton:      spi_write_data
 * @brief:          写数据函数
 * @param{data}:    写入的具体的数据
 * @retval:         NULL
 */
static void spi_write_data(uint8_t data) {
    spi_dev.set_dc(1);
    spi_dev.set_cs(0);
    spi_dev.spi_transbyte(data);
    spi_dev.set_cs(1);
    spi_dev.set_dc(1);
}


// TODO:目前无法支持多个SPI—LCD设备
#if SSD1680_ENABLE
void lcd_fn_register(SSD1680_SPI* lcd_dev) {
    lcd_dev->dev = &spi_dev;
    lcd_dev->write_cmd = spi_write_cmd;
    lcd_dev->write_data = spi_write_data;
    lcd_dev->read_busy = SPI_READ_BUSY;
    lcd_dev->set_reset = PSI_SET_RESET;
}
#endif


