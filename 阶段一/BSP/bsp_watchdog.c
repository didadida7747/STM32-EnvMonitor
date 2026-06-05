#include "bsp_watchdog.h"

/* 
 * 阶段一：只初始化看门狗结构，但不使能。
 * 等第三轮集成联调全部稳定后，再调用 BSP_Watchdog_Enable() 打开。
 */
void BSP_Watchdog_Init(void)
{
    /* 使能看门狗时钟（写入保护密钥） */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    
    /* 设置预分频器：40kHz / 64 = 625 Hz */
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    
    /* 
     * 设置重装载值：要达到1.5秒超时
     * 超时时间 = (1 / 625) * 重装载值
     * 重装载值 = 1.5 * 625 ≈ 937
     */
    IWDG_SetReload(937);
    
    /* 喂一次狗，将重装载值载入计数器 */
    IWDG_ReloadCounter();
    
    /* 
     * 阶段一不使能，等系统稳定后再调用 BSP_Watchdog_Enable()。
     * 使能代码：IWDG_Enable();
     */
}

void BSP_Watchdog_Enable(void)
{
    IWDG_Enable();  /* 启动独立看门狗，一旦启动无法软件关闭 */
}

void BSP_Watchdog_Reload(void)
{
    IWDG_ReloadCounter();  /* 喂狗，执行时间 <1us */
}