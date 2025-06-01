#include "oledTask.h"
#include "OLED.h"
#include "car.h"
#include "cmsis_os.h"

extern float Med_Angle;            // 目标倾角 | Target angle (unused here)
extern float Target_Speed;         // 目标速度 | Target speed (unused here)
extern float Vertical_Kp;          // 直立环 Kp | Vertical loop Kp
extern float Vertical_Kd;          // 直立环 Kd | Vertical loop Kd
extern float Velocity_Kp;          // 速度环 Kp | Velocity loop Kp
extern float Velocity_Ki;          // 速度环 Ki | Velocity loop Ki
extern float Turn_Kp;              // 转向环 Kp | Turn loop Kp

extern uint8_t cnt;                // 当前页面索引 | Current page index

extern Car car;

uint16_t encoder_count1;           // 编码器计数1 | Encoder count 1 (unused here)
uint16_t encoder_count2;           // 编码器计数2 | Encoder count 2 (unused here)

/**
  * @brief   根据 cnt 显示不同页面内容 | Display different pages based on cnt
  * @note    使用 OLED_Printf 打印小车状态、PID 参数、IMU 数据等 | Use OLED_Printf to show car status, PID params, IMU data, etc.
  */
void ShowPages(void) {
    switch (cnt) {
        case 0:
            // 标题栏居中显示 | Center title
            OLED_Printf((128 - 10 * 6) / 2, 0, OLED_6X8, "BalanceCar", car.imu.roll);
            OLED_Printf((128 - 12 * 6) / 2, 1 * 8, OLED_6X8, "Car States");
            // 显示线速度和角速度 | Show linear and angular speeds
            OLED_Printf(0, 2 * 8, OLED_6X8, "Linear Speed: %d", car.targetLinearSpeed);
            OLED_Printf(0, 3 * 8, OLED_6X8, "Angular Speed:   %d", car.targetAngularSpeed);
            // 显示刹车状态 | Show brake status
            OLED_Printf(0, 4 * 8, OLED_6X8, "IsBrake: 	 %d", car.isBrake);
            // 显示电池电量示例 | Show battery example
            OLED_Printf(0, 5 * 8, OLED_6X8, "Battery: 	 %3.2f", 0.9f);
            // 显示蓝牙在线/离线 | Show BT online/offline
            if (car.isBluetoothConnected)
                OLED_Printf(0, 6 * 8, OLED_6X8, "BT State: Online");
            else
                OLED_Printf(0, 6 * 8, OLED_6X8, "BT State: Offline");
            // 显示起始速度 | Show initial speed
            OLED_Printf(0, 7 * 8, OLED_6X8, "Init_t_s: %d", car.targetStartLinearSpeed);
            break;

        case 1:
            OLED_Printf((128 - 10 * 6) / 2, 0, OLED_6X8, "BalanceCar", car.imu.roll);
            OLED_Printf((128 - 13 * 6) / 2, 1 * 8, OLED_6X8, "PID Parameter");
            // 显示直立环参数 | Show vertical loop params
            OLED_Printf(0, 2 * 8, OLED_6X8, "Vertical");
            OLED_Printf(0, 3 * 8, OLED_6X8, "Kp:%.1f", Vertical_Kp);
            OLED_Printf(0, 4 * 8, OLED_6X8, "KD:%.1f", Vertical_Kd);
            // 显示速度环参数 | Show velocity loop params
            OLED_Printf(0, 5 * 8, OLED_6X8, "Velocity");
            OLED_Printf(0, 6 * 8, OLED_6X8, "Kp:%.1f", Velocity_Kp);
            OLED_Printf(0, 7 * 8, OLED_6X8, "KD:%.3f", Velocity_Ki);
            break;

        case 2:
            OLED_Printf((128 - 10 * 6) / 2, 0, OLED_6X8, "BalanceCar", car.imu.roll);
            OLED_Printf((128 - 8 * 6) / 2, 1 * 8, OLED_6X8, "Car cmd");
            // 显示当前命令 ID | Show current command ID
            OLED_Printf(0, 2 * 8, OLED_6X8, "CMD ID:  %d", car.cmd);
            break;

        case 3:
            OLED_Printf((128 - 10 * 6) / 2, 0, OLED_6X8, "BalanceCar", car.imu.roll);
            OLED_Printf((128 - 8 * 6) / 2, 1 * 8, OLED_6X8, "IMU Data");
            // 显示俯仰角和陀螺仪 y 轴角速度 | Show pitch and gyro-y
            OLED_Printf(0, 2 * 8, OLED_6X8, "Pitch:  %3.1f", car.imu.roll);
            OLED_Printf(0, 3 * 8, OLED_6X8, "Gyro-y: %3.1f", car.imu.gyrox);
            break;

        case 4:
            OLED_Printf((128 - 10 * 6) / 2, 0, OLED_6X8, "BalanceCar", car.imu.roll);
            OLED_Printf((128 - 12 * 6) / 2, 1 * 8, OLED_6X8, "Encoder Data");
            // 显示左右编码器 RPM | Show left/right encoder RPM
            OLED_Printf(0, 2 * 8, OLED_6X8, "Encoder RPM");
            OLED_Printf(0, 3 * 8, OLED_6X8, "Left:   %3.1f", car.encoder_l.rpm);
            OLED_Printf(0, 4 * 8, OLED_6X8, "Right:  %3.1f", car.encoder_r.rpm);
            break;

        default:
            break;
    }
    OLED_Update();  // 刷新 OLED 显示 | Refresh OLED display
}

/**
  * @brief   OLED 任务入口 | OLED task entry
  * @param   arguments 任务参数（未使用） | Task arguments (unused)
  * @note    周期性调用 ShowPages 并延时 | Periodically call ShowPages and delay
  */
void StartOledTask(void const *arguments) {
    while (1) {
        ShowPages();      // 显示当前页面 | Display the current page
        osDelay(100);     // 延时 100ms | Delay 100ms
    }
}
