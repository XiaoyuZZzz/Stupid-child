# FLASH日志设计文档



| 版本号 | 修改说明                 | 时间       | 作者   |
| ------ | ------------------------ | ---------- | ------ |
| V1.0   | 1.Flash日志文档设计      | 2025-08-01 | shuyu  |
| V1.0   | 1. FLASH日志文档设计完善 | 2025-08-03 | shuyuu |



## 1.FLASH日志核心使用

### FLASH日志核心设计

> 基于FLASH的不易失性做日志存储再好不过，但是考虑到不同大小的单片机的flash大小不一致，有的单片机flash紧凑，无法开辟大量的flash做日志存储，因此本设计应该基于小FLASH存储设计
>
> 1. FLASH的设计范围不应该太大
> 2. FLASH的设计应该简洁
> 3. 日志打印应该考虑RTT、UART打印，应需要打印回调
> 4. 日志需要保存时间戳

---

#### FLASH表格

flash表格主要存储的是整个日志的信息，日志信息包括三个模块。

- 模块一：错误信息
- 模块二：普通信息
- 模块三：原始数据

#### FLASH模块

FLASH模块是一个结构体

```
typedef struct {
    uint32_t    sector_size;                    // 扇区大小(字节)
    uint32_t    head_offset;                    // 扇区内偏移，应该为下一条数据写入的起始地址
    uint32_t    log_count;                      // 日志的数量
}FLASH_MANEGER;
```

这样设计是为了写入文件时判断是否超出扇区大小，读取文件的时候能够通过日志数量判断索引是否超出范围。





初始化时应该读取标志位是否写入，如果没有写入标志位为0xFF，写入之后得到标志位为0xAA

#### FLASH包内容

```
typedef struct {
    uint32_t timestamp;                             /*时间戳 */
    uint32_t event_id;                              /*事件id*/
    uint8_t  data[SUPPORT_MAX_WRITE_SIZE];          /*写入的数据 */
}LOG_PACK;
```

:exclamation:FLASH的写入需要擦除，因此这个设计是预留作为PVD中断，写入最后一条数据的。功能还未完善。



因此FLASH的日志库只能够写入，目前读取只能够通过j-flash或者读取接口f_log_read获取，怎么打印需要用户自己的修改

## 2.FLASH日志使用说明

用户在`sc_conf.h`中，开启`DEBUG_ENABLE`,选择`DEBUG_TARGETS`中的`DEBUG_FLASH_BIT`

调用接口`flash_log_init`进行初始化

调用`f_log_write`进行写入数据

调用`f_log_readf_log_read`进行读取参数

## 3. FLASH日志参数说明

在`sc_conf.h`中进行参数修改

```
#define SEND_CHAR                   send_char               //注册用户底层的发送字节函数
#define SUPPORT_DEBUG_LEN           (128)                   //默认支持128字节的长度调试

#endif
#if (DEBUG_TARGETS & DEBUG_FLASH_BIT) 

#define FLASH_DEBUG_ENABLE

#define SUPPORT_MAX_WRITE_SIZE      (16)                                                //支持最大写入的数据大小
#define WRITE_FLAG                  (0xAA)                                              //写入标志位

#define FLASH_USER_START_ADDR       (0x08000000ul)                                      // 默认FLASH的起始地址为0x08000000
#define FLASH_APP_SIZE              (1024 * 100)                                        // 默认FLASH中APP区大小为100K字节

/*如果使用ST芯片，API为擦除扇区，最好是扇区的起始地址，起始地址用来存放一个表格结构体，作为信息管理 */
/*默认采用的是STM32F4的最后一个扇区作为开发测试 */
#define FLASH_LOG_START_ADDR		(0x08040000)
#define FLASH_START_ADDR            (FLASH_LOG_START_ADDR )           					// 默认FLASH日志起始地址
#define FLAHS_SUPPOR_SIZE           (1024 * 6)                                          // 默认FLASH日志支持6K字节的存储
#define FLASH_SECTOR_SIZE           (FLAHS_SUPPOR_SIZE / 3)                             // 默认每个模块大小为2K字节

/* 用户注册函数 */
#define FLASH_WRITE_FUNC            (mcu_flash_wirte)           
#define FLASH_READ_FUNC             (mcu_flash_read)
#define FLASH_ERASE_FUNC            (mcu_flash_erase)
```

将自己实现的底层读写函数进行注册即可，

函数的格式为

```
typedef struct {
    uint8_t (*flash_write)(uint32_t addr,uint32_t* write_buff,uint32_t wite_len);
    uint8_t (*flash_read)(uint32_t addr,uint32_t* read_buff,uint32_t read_len);
    uint8_t (*flash_earse)(uint32_t addr,uint32_t ears_len);
}FLASH_OPS;
```



## 4. FLASH日志注意事项

- FLASH注意写入的地址需要4字节对齐，因此`FLASH_LOG_START_ADDR`一定是4字节对齐的

