#include "bsp_led.h"

/* 使用PC13作为调试LED（许多最小系统板默认连接） */
#define LED_PORT    GPIOC
#define LED_PIN     GPIO_Pin_13
#define LED_CLK     RCC_APB2Periph_GPIOC

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 使能GPIO时钟 */
    RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);
    
    /* 配置为推挽输出 */
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    
    /* 初始熄灭 */
    BSP_LED_Off();
}

void BSP_LED_On(void)
{
    GPIO_ResetBits(LED_PORT, LED_PIN);  /* PC13低电平点亮（常见设计） */
}

void BSP_LED_Off(void)
{
    GPIO_SetBits(LED_PORT, LED_PIN);    /* 高电平熄灭 */
}

void BSP_LED_Toggle(void)
{
    /* 读取当前输出电平，取反写入 */
    if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN))
    {
        GPIO_ResetBits(LED_PORT, LED_PIN);
    }
    else
    {
        GPIO_SetBits(LED_PORT, LED_PIN);
    }
}
