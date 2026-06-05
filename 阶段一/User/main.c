/* 阶段一验证：让LED以2Hz频率闪烁，证明系统运行 */

#include "main.h"
#include "bsp_led.h"
#include "bsp_watchdog.h"
#include <string.h>

//// 全局变量(system_globals.h已取代)
//float g_current_temp  = 0.0f;
//float g_target_temp   = 25.0f;
//uint8_t g_valve_percent = 0;

// 定义全局结构体变量（零初始化，位于 .bss 段）
System_t g_sys;

// 函数声明
void System_Init(void);
/* 前向声明各模块初始化函数 */
void BSP_UART_Init(void);
void BSP_I2C_Init(void);
void BSP_Sensor_Init(void);
void BSP_OLED_Init(void);
void BSP_ADC_Init(void);
void BSP_DMA_Init(void);
void BSP_PWM_RGB_Init(void);
void BSP_Alarm_Init(void);
void BSP_Button_Init(void);
void BSP_Timer_Init(void);
void BSP_EXTI_Init(void);
void Lib_SoftTimer_Init(void);
void Lib_RingBuf_Init(void);
void App_StateMachine_Init(void);
void App_StateMachine_Run(void);

///* 时钟配置：72MHz，使用外部8MHz晶振 */
////通用型，F1可用系统自带的`SystemInit()`
//static void SystemClock_Config(void)
//{
//    /* 这里根据你的板子，填入标准时钟配置代码 */
//    /* 基本步骤：使能HSE -> 等待就绪 -> 配置PLL -> 选择PLL作为系统时钟 */
//}

void SysTick_Handler(void)
{
	g_sys.sys_tick_ms++;/* 系统时间基准，递增 */
}

int main(void)
{
	/* ---------- 基础初始化 ---------- */
    SystemInit();     // 配置系统时钟72MHz（需自行实现或使用默认）
//    Delay_ms(100);   没有必要延时
//	//  死等100ms的更优雅解法
//	//	SystemInit();   // 配置72MHz

//	//// 轮询：确认系统时钟已经切换到PLL输出（即72MHz生效）
//	//while(RCC_GetSYSCLKSource() != 0x08)  // 0x08 表示 PLL 作为系统时钟源
//	//{
//	//    // 等待时钟切换完成，不做任何事
//	//}

//	//// 如果还想更稳，可以再加检查PLL是否就绪
//	//while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

//	//// 现在可以安全地初始化外设了
//	//LED_Init();
//	//UART1_Init();
	SysTick_Config(SystemCoreClock / 1000);  /* 配置SysTick每1ms中断一次 */
    __disable_irq();  /* 暂时关闭全局中断，初始化完成后统一开启 */
	
	System_Init();   // 初始化全局结构体
	/* 3. 初始化各个硬件模块（阶段一只初始化LED和看门狗，其他先调用空函数） */
    BSP_LED_Init();
    BSP_Watchdog_Init();     /* 配置看门狗，但不使能 */
    BSP_Timer_Init();
    Lib_SoftTimer_Init();
    
    BSP_UART_Init();
    BSP_I2C_Init();
    BSP_Sensor_Init();
    BSP_OLED_Init();
    BSP_ADC_Init();
    BSP_DMA_Init();
    BSP_PWM_RGB_Init();
    BSP_Alarm_Init();
    BSP_Button_Init();
    BSP_EXTI_Init();
    Lib_RingBuf_Init();
    App_StateMachine_Init();
	
	/* 4. 开启全局中断 */
    __enable_irq();
	
	/* 5. 阶段一验证：让LED以2Hz频率闪烁，证明系统运行 */
    /* 使用非阻塞方式，不调用delay_ms */
    uint32_t last_toggle_tick = 0;
	
	while(1)
	{
		uint32_t now = g_sys.sys_tick_ms;
        
        /* 每250ms翻转一次LED（周期500ms，即2Hz） */
        if (now - last_toggle_tick >= 250)
        {
            BSP_LED_Toggle();
            last_toggle_tick = now;
        }
        
        /* 喂狗（此时看门狗已配置但未使能，这是预留的喂狗点） */
        BSP_Watchdog_Reload();
	}
}

void System_Init(void)
{
    // 方法1：用 memset 将所有字节清零（适合结构体没有指针/动态内存的情况）
    memset(&g_sys, 0, sizeof(g_sys));
    
    // 方法2：也可以逐个字段赋值（更明确，但不适合字段很多的场合）
    // g_sys.initialized = false;
    // g_sys.tick_count = 0;
    // g_sys.temperature = 0.0f;
    // g_sys.pressure = 0.0f;
    
    // 然后设置一些合理的初始值
    g_sys.temp_threshold_default = 35.0f;    // 例如 25 度作为默认初始温度
}
