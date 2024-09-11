#pragma once

// #define STM32F0xx_MCUCONF

#define ENCODER_A_PINS { A4 }
#define ENCODER_B_PINS { A5 }
#define ENCODER_DIRECTION_FLIP
#define DIP_SWITCH_PINS { A6 }

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7