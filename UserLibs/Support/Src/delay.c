#include "main.h"

#define USE_HAL_LEGACY
#include "stm32_hal_legacy.h"

// 时基源选择：1=SysTick，0=其他定时器（使用FreeRTOS时）
// Timebase source selection: 1=SysTick, 0=other timer (when using FreeRTOS)
//#define Timebase_Source_is_SysTick 1
#define Timebase_Source_is_SysTick 0

#if (!Timebase_Source_is_SysTick)
extern TIM_HandleTypeDef htim5;       // 使用FreeRTOS时的定时器句柄 | Timer handle when using FreeRTOS
#define Timebase_htim htim5

// 定时器计数器和自动重装载值宏 | Timer counter and autoreload value macros
#define Delay_GetCounter()    __HAL_TIM_GetCounter(&Timebase_htim)
#define Delay_GetAutoreload() __HAL_TIM_GetAutoreload(&Timebase_htim)
#else
// SysTick 计数器和重装载值宏 | SysTick counter and reload value macros
#define Delay_GetCounter()    (SysTick->VAL)
#define Delay_GetAutoreload() (SysTick->LOAD)
#endif

// 延时因子，fac_us：微秒因子，fac_ms：毫秒因子 | Delay factors: fac_us = microsecond factor, fac_ms = millisecond factor
static uint16_t fac_us = 0;
static uint32_t fac_ms = 0;

/**
  * @brief   初始化延时函数 | Initialize delay functions
  * @note    根据时基源计算微秒和毫秒因子 | Compute microsecond and millisecond factors based on timebase
  */
void delay_init(void) {
#if (!Timebase_Source_is_SysTick)
    fac_ms = 1000000;           // 假设定时器 1MHz | Assume timer runs at 1MHz
    fac_us = fac_ms / 1000;     // 计算微秒因子 | Compute microsecond factor
#else
    fac_ms = SystemCoreClock / 1000;  // 根据系统时钟计算毫秒因子 | Compute millisecond factor
    fac_us = fac_ms / 1000;           // 计算微秒因子 | Compute microsecond factor
#endif
}

/**
  * @brief   微秒延时 | Delay in microseconds
  * @param   nus  需要延时的微秒数 | Number of microseconds to delay
  */
void delay_us(uint32_t nus) {
    uint32_t ticks = 0;   // 所需滴答数 | Required ticks
    uint32_t told = 0;    // 上一次计数值 | Previous counter value
    uint32_t tnow = 0;    // 当前计数值 | Current counter value
    uint32_t tcnt = 0;    // 累计滴答数 | Accumulated ticks
    uint32_t reload = 0;  // 自动重装载值 | Autoreload value

    reload = Delay_GetAutoreload();      // 获取重装载值 | Get autoreload value
    ticks = nus * fac_us;                // 计算所需滴答数 | Calculate required ticks
    told = Delay_GetCounter();           // 获取初始计数 | Get initial counter

    while (1) {
        tnow = Delay_GetCounter();       // 获取当前计数 | Get current counter
        if (tnow != told) {              // 若计数变化 | If counter changed
            if (tnow < told) {           // 处理计数回绕 | Handle overflow
                tcnt += told - tnow;
            } else {
                tcnt += reload - tnow + told;
            }
            told = tnow;                 // 更新上次计数 | Update previous value
            if (tcnt >= ticks) break;    // 达到延时，退出 | Delay complete, exit
        }
    }
}

/**
  * @brief   毫秒延时 | Delay in milliseconds
  * @param   nms  需要延时的毫秒数 | Number of milliseconds to delay
  */
void delay_ms(uint32_t nms) {
    uint32_t ticks = 0;   // 所需滴答数 | Required ticks
    uint32_t told = 0;    // 上一次计数值 | Previous counter value
    uint32_t tnow = 0;    // 当前计数值 | Current counter value
    uint32_t tcnt = 0;    // 累计滴答数 | Accumulated ticks
    uint32_t reload = 0;  // 自动重装载值 | Autoreload value

    reload = Delay_GetAutoreload();      // 获取重装载值 | Get autoreload value
    ticks = nms * fac_ms;                // 计算所需滴答数 | Calculate required ticks
    told = Delay_GetCounter();           // 获取初始计数 | Get initial counter

    while (1) {
        tnow = Delay_GetCounter();       // 获取当前计数 | Get current counter
        if (tnow != told) {              // 若计数变化 | If counter changed
            if (tnow < told) {           // 处理计数回绕 | Handle overflow
                tcnt += told - tnow;
            } else {
                tcnt += reload - tnow + told;
            }
            told = tnow;                 // 更新上次计数 | Update previous value
            if (tcnt >= ticks) break;    // 达到延时，退出 | Delay complete, exit
        }
    }
}

/**
  * @brief   重写 HAL_Delay（以与 FreeRTOS 兼容） | Override HAL_Delay (compatible with FreeRTOS)
  * @param   Delay  延时毫秒数 | Delay in milliseconds
  */
void HAL_Delay(uint32_t Delay) {
    uint32_t tickstart = HAL_GetTick(); // 获取开始时刻 | Get start tick
    uint32_t wait = Delay;              // 等待时长 | Wait duration

    // 若需要最小延时，可启用以下代码 | To enforce minimum delay, uncomment below
    // if (wait < HAL_MAX_DELAY) {
    //     wait += (uint32_t)(uwTickFreq);
    // }

    while ((HAL_GetTick() - tickstart) < wait) {
        // 空循环等待 | Busy-wait
    }
}
