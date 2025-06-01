#ifndef ENCODER_H_
#define ENCODER_H_

#include "main.h"
#include "tim.h"

typedef struct Encoder Encoder;

struct Encoder{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint16_t count;
	uint16_t last_count;
	float rpm;
	uint16_t (*GetCountAndRpm)(Encoder* self);
};

Encoder newEncoder(TIM_HandleTypeDef *htim,	uint32_t Channel);
uint16_t GetCountAndRpm(Encoder* self);
int16_t GetRPM(Encoder* self);
#endif
