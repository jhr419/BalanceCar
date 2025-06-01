#include "car.h"
#include "pid.h"
#include "communication.h"
#include "cmsis_os.h"

// 全局小车对象 | Global car instance
Car car;

// PID 输出变量 | PID output variables
int Vertical_out, Velocity_out, Turn_out;

/**
  * @brief   创建并初始化小车实例 | Create and initialize a car instance
  * @return  返回初始化后的 Car 对象 | Returns the initialized Car object
  */
Car newCar(void) {
    Car c = {
            .isObstacleAvoidanceOn = FALSE,    // 障碍规避标志 | Obstacle avoidance flag
            .isObstacleDetected    = FALSE,    // 障碍检测标志 | Obstacle detected flag
            .isBluetoothConnected  = TRUE,     // 蓝牙连接状态 | Bluetooth connection status
            .isBrake               = FALSE,    // 刹车标志 | Brake flag
            .motionState           = CAR_MOTION_STOP, // 当前运动状态 | Current motion state
            .targetLinearSpeed     = 0,        // 目标线速度 | Target linear speed
            .targetAngularSpeed    = 0,        // 目标角速度 | Target angular speed
            .targetStartLinearSpeed= 8,        // 初始启动速度 | Initial start speed
            .balanceBias           = MECHANICAL_BALANCE_BIAS, // 平衡偏置 | Balance bias
            .cmd                   = CMD_STOP  // 默认命令 | Default command
    };

    // 左电机初始化参数 | Left motor init parameters
    Motor_InitTypeDef motor_l_Init = {
            .htim         = &MOTOR_TIM,
            .Channel      = MOTOR_L_CHANNEL,
            .IN1_GPIOx    = MOTOR_L_IN1_PORT,
            .IN1_GPIO_Pin = MOTOR_L_IN1_PIN,
            .IN2_GPIOx    = MOTOR_L_IN2_PORT,
            .IN2_GPIO_Pin = MOTOR_L_IN2_PIN
    };

    // 右电机初始化参数 | Right motor init parameters
    Motor_InitTypeDef motor_r_Init = {
            .htim         = &MOTOR_TIM,
            .Channel      = MOTOR_R_CHANNEL,
            .IN1_GPIOx    = MOTOR_R_IN1_PORT,
            .IN1_GPIO_Pin = MOTOR_R_IN1_PIN,
            .IN2_GPIOx    = MOTOR_R_IN2_PORT,
            .IN2_GPIO_Pin = MOTOR_R_IN2_PIN
    };

    // 创建左右电机对象 | Create motor instances
    c.motor_l = newMotor(motor_l_Init);
    c.motor_r = newMotor(motor_r_Init);

    // 初始化左右编码器 | Initialize encoders
    c.encoder_l = newEncoder(&ENCODER_L_TIM, TIM_CHANNEL_ALL);
    c.encoder_r = newEncoder(&ENCODER_R_TIM, TIM_CHANNEL_ALL);

    // 初始化并启用 IMU | Initialize and enable IMU
    c.imu = newImu();
    c.imu.Enable(&c.imu);

    // 启用电机驱动板 | Enable motor driver board (set STBY high)
    HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);

    // 绑定移动函数 | Bind move function
    c.CarMove = CarMove;

    return c;
}

/**
  * @brief   计算电机 PID 输出 | Compute motor PID output
  * @return  返回 PWM 输出 | Returns PWM output
  *
  * @note    先限幅角速度，再调用速度-直立-转向 PID | Limit angular speed, then run velocity, vertical, and turn PID
  */
int MotorPidCalc() {
    // 限制角速度范围 | Limit angular speed range
    car.targetAngularSpeed = LIMIT(car.targetAngularSpeed, -5000, 5000);

    // 速度 PID 输出 | Velocity PID output
    Velocity_out = VelocityPidCalc(car.targetLinearSpeed, car.encoder_l.rpm, car.encoder_r.rpm);
    // 直立 PID 输出 | Vertical PID output
    Vertical_out = VerticalPidCalc(Velocity_out + car.balanceBias, car.imu.roll, car.imu.gyrox);
    // 转向 PID 输出 | Turn PID output
    Turn_out = Turn(car.targetAngularSpeed);

    return Vertical_out;  // 直立环输出 | Return vertical loop output
}

/**
  * @brief   解析并处理运动命令 | Parse and process motion commands
  * @note    根据 car.cmd 更新目标速度和状态 | Update target speeds and state based on car.cmd
  */
void checkMotionCommand() {
    // 如果开启障碍规避且刹车，强制后退 | If obstacle avoidance on and brake, force backward
    if (car.isObstacleAvoidanceOn && car.isBrake) {
        car.cmd = CMD_BACKWARD;
    }

    switch (car.cmd) {
        case CMD_STOP:
            car.targetLinearSpeed = 0;   // 停止 | Stop
            car.targetAngularSpeed = 0;
            break;

        case CMD_FORWARD:
            // 前进可能是新状态，也可能重复 | Forward may be new or repeated state
            car.targetLinearSpeed = (int8_t)car.targetStartLinearSpeed;
            car.motionState = CAR_MOTION_FOWARD;  // 更新状态 | Update state
            break;

        case CMD_BACKWARD:
            car.targetLinearSpeed = (int8_t)-car.targetStartLinearSpeed;  // 后退速度 | Backward speed
            car.motionState = CAR_MOTION_BACKWARD;  // 更新状态 | Update state
            break;

        case CMD_LEFT:
            car.targetAngularSpeed = -3000;   // 左转角速度 | Left turn angular speed
            car.motionState = CAR_MOTION_LEFT;  // 更新状态 | Update state
            break;

        case CMD_RIGHT:
            car.targetAngularSpeed = 3000;    // 右转角速度 | Right turn angular speed
            car.motionState = CAR_MOTION_RIGHT; // 更新状态 | Update state
            break;

        case CMD_SPEED_UP:
            if (car.motionState == CAR_MOTION_FOWARD) {
                car.targetLinearSpeed += 1;  // 加速前进 | Accelerate forward
            } else if (car.motionState == CAR_MOTION_BACKWARD) {
                car.targetLinearSpeed -= 1;  // 加速后退 | Accelerate backward
            }
            car.cmd = CMD_SPEED_CONSTANT;   // 固定速度状态 | Constant speed state
            break;

        case CMD_SPEED_DOWN:
            if (car.motionState == CAR_MOTION_FOWARD) {
                if (car.targetLinearSpeed > 2) {
                    car.targetLinearSpeed -= 2;  // 减速前进 | Decelerate forward
                }
            } else if (car.motionState == CAR_MOTION_BACKWARD) {
                if (car.targetLinearSpeed < -2) {
                    car.targetLinearSpeed += 2;  // 减速后退 | Decelerate backward
                }
            }
            car.cmd = CMD_SPEED_CONSTANT;  // 固定速度状态 | Constant speed state
            break;

        case CMD_STOP_SLOWLY:
            // 缓慢停止：前进速度大于等于4时减1 | Slow stop: if forward speed ≥4, reduce by1
            if (car.targetLinearSpeed >= 4) car.targetLinearSpeed -= 1;
            car.targetAngularSpeed = 0;  // 角速度置零 | Angular speed zero
            break;

        case CMD_POWER_SWITCH:
            HAL_GPIO_TogglePin(STBY_GPIO_Port, STBY_Pin);  // 切换电机驱动板电源 | Toggle motor driver board power
            car.cmd = CMD_SPEED_CONSTANT;  // 固定速度状态 | Constant speed state
            break;

        case CMD_ROAD_PLANNING:
            car.isObstacleAvoidanceOn = BOOL_TOGGLE(car.isObstacleAvoidanceOn);  // 切换障碍规避模式 | Toggle obstacle avoidance mode
            car.cmd = CMD_SPEED_CONSTANT;
            break;

        default:
            break;
    }

    // 限制线速度范围 | Limit linear speed range
    car.targetLinearSpeed = LIMIT(car.targetLinearSpeed, -40, 40);
}

/**
  * @brief   小车移动控制函数 | Car movement control function
  * @param   self      指向 Car 对象的指针 | Pointer to Car object
  * @param   setSpeed  未使用参数，可保留 | Unused parameter, can be retained
  * @note    调用 PID 计算，判断刹车条件，并设置左右电机 PWM | Run PID, check brake, set left/right motor PWM
  */
void CarMove(Car *self, int8_t setSpeed) {
    int32_t PWM_out, motor_l_pwm, motor_r_pwm;

    checkMotionCommand();  // 更新目标速度 | Update target speeds
    PWM_out = MotorPidCalc();  // 计算 PID 输出 | Compute PID output

    // 倾角过大时刹车 | Brake if tilt angle too large
    if (car.imu.roll > 60 || car.imu.roll < -60) {
        car.isBrake = 1;
    } else {
        car.isBrake = 0;
    }

    // 左右电机 PWM 计算 | Compute left/right motor PWM
    motor_l_pwm = PWM_out - Turn_out;              // 左电机输出 | Left motor output
    motor_r_pwm = PWM_out + (int32_t)(0.8f * Turn_out);  // 右电机输出 | Right motor output

    // 限制 PWM 范围 | Limit PWM range
    motor_l_pwm = LIMIT(motor_l_pwm, -30000, 30000);
    motor_r_pwm = LIMIT(motor_r_pwm, -30000, 30000);

    // 发送 PWM 给电机并处理刹车 | Send PWM to motors and handle brake
    self->motor_l.Move(&self->motor_l, car.isBrake, motor_l_pwm);
    self->motor_r.Move(&self->motor_r, car.isBrake, motor_r_pwm);
}
