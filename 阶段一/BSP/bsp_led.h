#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

void BSP_LED_Init(void);
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);

#endif /* __BSP_LED_H */
