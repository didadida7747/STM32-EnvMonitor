#ifndef __BSP_WATCHDOG_H
#define __BSP_WATCHDOG_H

#include "stm32f10x.h"

void BSP_Watchdog_Init(void);
void BSP_Watchdog_Enable(void);
void BSP_Watchdog_Reload(void);

#endif /* __BSP_WATCHDOG_H */
