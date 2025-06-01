#include "filter.h"
#include "string.h"

/**
  * @brief   初始化滤波器实例 | Initialize the filter instance
  * @param   filter           滤波器结构体指针 | Pointer to MotorVoltageFilter struct
  * @param   initial_voltage  初始电压值，用于填充缓冲区 | Initial voltage value to fill the buffer
  * @return  无 | None
  *
  * @note    将 buffer 所有元素设为 initial_voltage，并将 index 和 filtered_value 初始化为 initial_voltage
  *          Sets all buffer elements to initial_voltage and initializes index and filtered_value to initial_voltage
  */
void Filter_Init(MotorVoltageFilter *filter, int16_t initial_voltage) {
    for (uint8_t i = 0; i < FILTER_WINDOW_SIZE; i++) {
        filter->buffer[i] = initial_voltage;  /**< 环形缓冲区填充初始值 | Fill circular buffer with initial value */
    }
    filter->index = 0;                      /**< 索引归零 | Reset index */
    filter->filtered_value = initial_voltage;  /**< 滤波后值初始化 | Initialize filtered_value */
}

/**
  * @brief   对数组进行改进的带符号冒泡排序 | Perform improved signed bubble sort
  * @param   buf   待排序数组指针 | Pointer to the array to sort
  * @param   size  数组长度 | Length of the array
  * @return  无 | None
  *
  * @note    使用异或交换法优化内存 | Uses XOR swap to avoid a temporary variable
  * @note    排序后用于去除极值 | Sorted array is used later to remove outliers
  */
static void Sort_Buffer(int16_t *buf, uint8_t size) {
    uint8_t swapped;
    do {
        swapped = 0;  /**< 标记本次是否发生交换 | Flag if a swap occurred this pass */
        for (uint8_t i = 0; i < size - 1; i++) {
            if (buf[i] > buf[i + 1]) {
                // 异或交换 | XOR swap to avoid temp variable
                buf[i] ^= buf[i + 1];
                buf[i + 1] ^= buf[i];
                buf[i] ^= buf[i + 1];
                swapped = 1;
            }
        }
        size--;
    } while (swapped);
}

/**
  * @brief   处理原始电压并返回滤波结果 | Process raw voltage and return filtered result
  * @param   filter       已初始化的滤波器实例指针 | Pointer to an initialized MotorVoltageFilter
  * @param   raw_voltage  当前采样的原始电压值，可正可负 | Current raw voltage sample (positive or negative)
  * @return  返回滤波后电压值 | Returns the filtered voltage value
  *
  * @note    算法流程：
  *          1. 将 raw_voltage 写入 buffer[index]，index 自增并环绕 -> 更新采样窗口
  *             Write raw_voltage into buffer[index], increment index (wrap around) -> update sampling window
  *          2. 将 buffer 复制到 temp_buf 并排序 -> 不破坏原始顺序
  *             Copy buffer to temp_buf and sort -> preserve original order
  *          3. 去掉首尾各 2 个极值后求均值（防脉冲干扰）
  *             Discard two highest and two lowest values, then average (remove spikes)
  *          4. 四舍五入计算并赋值 filtered_value, 返回结果
  *             Round the average and assign to filtered_value, return result
  */
int16_t Filter_Process(MotorVoltageFilter *filter, int16_t raw_voltage) {
    // 更新采样窗口（环形缓冲区）| Update sampling window (circular buffer)
    filter->buffer[filter->index] = raw_voltage;
    filter->index = (filter->index + 1) % FILTER_WINDOW_SIZE;  /**< 环绕索引 | Wrap index */

    // 复制到临时数组排序（不破坏原始数据顺序）| Copy to temp array for sorting
    int16_t temp_buf[FILTER_WINDOW_SIZE];
    memcpy(temp_buf, filter->buffer, sizeof(temp_buf));  /**< 复制缓冲区数据 | Copy buffer data */
    Sort_Buffer(temp_buf, FILTER_WINDOW_SIZE);           /**< 对临时数组排序 | Sort the temporary array */

    // 去掉首尾各 2 个极值后求和 | Sum after removing two highest and two lowest values
    int32_t sum = 0;
    for (uint8_t i = 2; i < FILTER_WINDOW_SIZE - 2; i++) {
        sum += temp_buf[i];
    }

    // 计算平均值（四舍五入）| Calculate average with rounding
    uint8_t valid_count = FILTER_WINDOW_SIZE - 4;
    filter->filtered_value = (int16_t)((sum + valid_count / 2) / valid_count);

    return filter->filtered_value;
}
