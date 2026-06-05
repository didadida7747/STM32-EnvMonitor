#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"   // 根据你的具体型号调整，例如 stm32f4xx.h

typedef enum {
    STATE_NORMAL = 0,
    STATE_ALARM,
    STATE_ALARM_ACKED,   /* 已确认报警（贪睡） */
    STATE_CONFIG         /* 配置模式 */
} SystemState_t;

// 定义全局状态结构体类型
typedef struct {
    SystemState_t state;
    uint32_t sys_tick_ms;    /* 系统毫秒计数器，由SysTick中断递增 */
    
    /* 传感器数据（最新值） */
    float temperature;
    float humidity;
    float pressure;
    float battery_voltage;
    
    /* 阈值 */
    float temp_threshold_default;   /* 默认阈值 */
    float temp_threshold_temp;      /* 临时阈值，0表示未设置 */
    
    /* 标志位 */
    uint8_t sensor_data_ready;      /* 1：有新传感器数据待处理 */
    uint8_t adc_data_ready;         /* 1：有新ADC数据待处理 */
    uint8_t uart_cmd_ready;         /* 1：收到完整串口命令 */
    uint8_t button_pressed;         /* 1：按键被按下 */
    
    /* 软件定时器 */
    uint32_t snooze_end_tick;       /* 贪睡结束时刻 */
    uint32_t config_timeout_tick;   /* 配置模式超时时刻 */
    
} System_t;

/* 全局系统实例，在main.c中定义 */
extern System_t g_sys;

#endif

// 定义全局状态结构体类型
//typedef struct {
//    // ----- 系统状态 -----
//    bool     initialized;
//    uint32_t tick_count;        // 来自 SysTick 中断的计数
//    uint32_t sys_time_ms;       // 系统运行毫秒数
//    
//    // ----- 外设句柄（标准库风格）-----
//    // 标准库中不需要像 HAL 那样的句柄结构体，多用全局指针或直接操作寄存器
//    // 这里主要存放一些状态标志和配置缓存
//    TIM_TypeDef  *sys_tim;      // 指向某个定时器的寄存器基址（如 TIM2）
//    USART_TypeDef *debug_uart;  // 调试串口寄存器基址
//    
//    // 或者用更简单的方式：只存放外设的初始化参数副本（如果需要）
//    struct {
//        uint32_t baudrate;
//        FunctionalState isEnabled;
//    } uart_config;
//    
//    // ----- 业务数据 -----
//    float temperature;
//    float pressure;
//    int16_t  adc_raw[4];
//    
//    // 如果你使用了外部模块，还可以加互斥锁（如果用了 RTOS）
//    // OS_Mutex *data_mutex;
//} SystemGlobals;

//// 全局变量声明
//extern SystemGlobals g_sys;
