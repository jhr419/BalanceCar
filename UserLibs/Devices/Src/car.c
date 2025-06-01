#include "car.h"
#include "pid.h"
#include "communication.h"
#include "cmsis_os.h"

// 定义全局小车对象
// Global car instance
Car car;

int Vertical_out, Velocity_out, Turn_out; // 直立环&速度环&转向环的输出变量

// 创建小车对象，初始化电机、编码器、IMU 和 PID 控制器
// Create a car instance and initialize motors, encoders, IMU, and PID controllers
Car newCar(void) {
  Car c = {
          .isObstacleAvoidanceOn = FALSE,
          .isObstacleDetected = FALSE,
          .isBluetoothConnected = TRUE,
          .isBrake = FALSE,
          .motionState = CAR_MOTION_STOP,
          .targetLinearSpeed = 0,
          .targetAngularSpeed = 0,
          .targetStartLinearSpeed = 8,
          .balanceBias = MECHANICAL_BALANCE_BIAS,
          .cmd = CMD_STOP
  };

  // 初始化左电机配置
  // Initialize left motor
  Motor_InitTypeDef motor_l_Init = {
          .htim        = &MOTOR_TIM,
          .Channel      = MOTOR_L_CHANNEL,
          .IN1_GPIOx    = MOTOR_L_IN1_PORT,
          .IN1_GPIO_Pin = MOTOR_L_IN1_PIN,
          .IN2_GPIOx    = MOTOR_L_IN2_PORT,
          .IN2_GPIO_Pin = MOTOR_L_IN2_PIN
  };

  // 初始化右电机配置
  // Initialize right motor
  Motor_InitTypeDef motor_r_Init = {
          .htim        = &MOTOR_TIM,
          .Channel      = MOTOR_R_CHANNEL,
          .IN1_GPIOx    = MOTOR_R_IN1_PORT,
          .IN1_GPIO_Pin = MOTOR_R_IN1_PIN,
          .IN2_GPIOx    = MOTOR_R_IN2_PORT,
          .IN2_GPIO_Pin = MOTOR_R_IN2_PIN
  };

  // 创建左右电机对象
  // Create motor instances
  c.motor_l = newMotor(motor_l_Init);
  c.motor_r = newMotor(motor_r_Init);

  // 初始化左右编码器
  // Initialize encoders
  c.encoder_l = newEncoder(&ENCODER_L_TIM, TIM_CHANNEL_ALL);
  c.encoder_r = newEncoder(&ENCODER_R_TIM, TIM_CHANNEL_ALL);

  // 初始化 IMU
  // Initialize IMU
  c.imu = newImu();
  c.imu.Enable(&c.imu); // 启用 IMU（初始化）

  // 启用电机驱动板（STBY 引脚拉高）
  // Enable motor driver board (set STBY high)
  HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);

  // 绑定小车移动函数
  // Bind move function
  c.CarMove = CarMove;

  return c;
}

int MotorPidCalc() {
  int PWM_out;

  car.targetAngularSpeed = LIMIT(car.targetAngularSpeed, -5000, 5000);

  Velocity_out = VelocityPidCalc(car.targetLinearSpeed, car.encoder_l.rpm, car.encoder_r.rpm);
  Vertical_out = VerticalPidCalc(Velocity_out + car.balanceBias, car.imu.roll, car.imu.gyrox);
  Turn_out = Turn(car.targetAngularSpeed);
  PWM_out = Vertical_out;
  return PWM_out;
}

void checkMotionCommand() {
  if(car.isObstacleAvoidanceOn && car.isBrake) car.cmd = CMD_BACKWARD;

  switch (car.cmd) {
    case CMD_STOP:
      car.targetLinearSpeed = 0;
      car.targetAngularSpeed = 0;
      break;
    case CMD_FORWARD:
      //发送前进指令的情况下，可能是从非前进到前进状态，也可能是前进已经在运行（此时无需执行多余命令）
      car.targetLinearSpeed = (int8_t) car.targetStartLinearSpeed;
      car.motionState = CAR_MOTION_FOWARD;
      break;
    case CMD_BACKWARD:
      car.targetLinearSpeed = (int8_t)-car.targetStartLinearSpeed;
      car.motionState = CAR_MOTION_BACKWARD;
    case CMD_LEFT:
      car.targetAngularSpeed = -3000;
      car.motionState = CAR_MOTION_LEFT;
      break;
    case CMD_RIGHT:
      car.targetAngularSpeed = 3000;
      car.motionState = CAR_MOTION_RIGHT;
      break;
    case CMD_SPEED_UP:
      if(car.motionState == CAR_MOTION_FOWARD){
        car.targetLinearSpeed += 1;
      }
      else if(car.motionState == CAR_MOTION_BACKWARD){
        car.targetLinearSpeed -= 1;
      }
      car.cmd = CMD_SPEED_CONSTANT;
      break;
    case CMD_SPEED_DOWN:
      if(car.motionState == CAR_MOTION_FOWARD){
        if(car.targetLinearSpeed > 2) car.targetLinearSpeed -= 2;
      }
      else if(car.motionState == CAR_MOTION_BACKWARD){
        if (car.targetLinearSpeed < -2) car.targetLinearSpeed += 2;
      }
      car.cmd = CMD_SPEED_CONSTANT;
      break;
    case CMD_STOP_SLOWLY:
      if(car.targetLinearSpeed >= 4) car.targetLinearSpeed -= 1;
      car.targetAngularSpeed = 0;
      break;
    case CMD_POWER_SWITCH:
      HAL_GPIO_TogglePin(STBY_GPIO_Port, STBY_Pin);
      car.cmd = CMD_SPEED_CONSTANT;
      break;
    case CMD_ROAD_PLANNING:
      car.isObstacleAvoidanceOn = BOOL_TOGGLE(car.isObstacleAvoidanceOn);
      car.cmd = CMD_SPEED_CONSTANT;
    default:
      break;
  }

  car.targetLinearSpeed = LIMIT(car.targetLinearSpeed, -40, 40);
}

// 小车移动控制函数
// Car movement control function
void CarMove(Car *self, int8_t setSpeed) {
  int32_t PWM_out, motor_l_pwm, motor_r_pwm;
  checkMotionCommand();
  PWM_out = MotorPidCalc();

  // 如果倾角过大，进行刹车
  // Brake if the tilt angle is too large
  if (car.imu.roll > 60 || car.imu.roll < -60) {
    car.isBrake = 1;
  } else {
    car.isBrake = 0;
  }

  motor_l_pwm = PWM_out - Turn_out; // 左电机
  motor_r_pwm = PWM_out + 0.8 * Turn_out; // 右电机

  motor_l_pwm = LIMIT(motor_l_pwm, -30000, 30000);
  motor_r_pwm = LIMIT(motor_r_pwm, -30000, 30000);

  self->motor_l.Move(&self->motor_l, car.isBrake, motor_l_pwm);
  self->motor_r.Move(&self->motor_r, car.isBrake, motor_r_pwm);
}
