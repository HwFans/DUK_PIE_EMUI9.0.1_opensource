/*
* Simple driver for Texas Instruments LM3630 LED Flash driver chip
* Copyright (C) 2017 Texas Instruments
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*/

#ifndef __LINUX_KTD3133_H
#define __LINUX_KTD3133_H

#define KTD3133_NAME "ktd3133"
#define DTS_COMP_KTD3133 "ktd,ktd3133"
#define KTD3133_SUPPORT "ktd3133_support"
#define KTD3133_I2C_BUS_ID "ktd3133_i2c_bus_id"
#define KTD3133_HW_ENABLE "ktd3133_hw_enable"
#define KTD3133_HW_EN_GPIO "ktd3133_hw_en_gpio"
#define KTD3133_HW_EN_DELAY "bl_on_lk_mdelay"
#define MAX_STR_LEN	50

/* base reg */
#define KTD3133_REG_DEV_ID				0x00
#define KTD3133_REG_SW_RESET			0x01
#define KTD3133_REG_STATUS				0x0A

/*config reg*/
#define KTD3133_REG_MODE			    0x02
#define KTD3133_REG_CONTROL			    0x03
#define KTD3133_REG_RATIO_LSB			0x04
#define KTD3133_REG_RATIO_MSB			0x05
#define KTD3133_REG_PWM			        0x06
#define KTD3133_REG_RAMP_ON				0x07
#define KTD3133_REG_TRANS_RAMP			0x08

#define KTD3133_VENDOR_ID               0x18

#define GPIO_DIR_OUT 1
#define GPIO_OUT_ONE 1
#define GPIO_OUT_ZERO 0

#define KTD3133_RW_REG_MAX  7
struct ktd3133_chip_data {
	struct device *dev;
	struct i2c_client *client;
	struct regmap *regmap;
	struct semaphore test_sem;
};

struct ktd3133_backlight_information {
	/* whether support ktd3133 or not */
	unsigned int ktd3133_support;
	/* which i2c bus controller ktd3133 mount */
	unsigned int ktd3133_i2c_bus_id;
	unsigned int ktd3133_hw_en;
	/* ktd3133 hw_en gpio */
	unsigned int ktd3133_hw_en_gpio;
	unsigned int ktd3133_reg[KTD3133_RW_REG_MAX];
	unsigned int bl_on_lk_mdelay;
	unsigned int ktd3133_level_lsb;
	unsigned int ktd3133_level_msb;
};

static int KTD3133_REG_RATIO_LSB_BRIGHTNESS[256] = {0x00,0x04,0x03,0x04,0x04,0x05,0x03,0x02,0x03,0x00,0x02,0x00,0x04,0x05,0x05,0x04,0x01,
			0x04,0x07,0x01,0x02,0x02,0x01,0x00,0x06,0x03,0x00,0x05,0x01,0x04,0x00,0x03,0x05,0x00,0x01,0x03,0x05,0x06,0x07,0x07,
			0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x06,0x05,0x04,0x03,0x01,0x00,0x06,0x05,0x03,0x01,0x07,0x05,0x03,0x00,0x06,0x03,
			0x01,0x06,0x03,0x00,0x05,0x02,0x07,0x04,0x01,0x06,0x02,0x07,0x04,0x00,0x04,0x01,0x05,0x01,0x06,0x02,0x06,0x02,0x06,
			0x02,0x06,0x02,0x05,0x01,0x05,0x01,0x04,0x00,0x04,0x07,0x03,0x06,0x02,0x05,0x00,0x04,0x07,0x02,0x05,0x01,0x04,0x07,
			0x02,0x05,0x00,0x03,0x06,0x01,0x04,0x07,0x02,0x05,0x00,0x03,0x06,0x00,0x03,0x06,0x01,0x03,0x06,0x01,0x03,0x06,0x01,
			0x03,0x06,0x00,0x03,0x05,0x00,0x02,0x05,0x07,0x02,0x04,0x06,0x01,0x03,0x05,0x00,0x02,0x04,0x07,0x01,0x03,0x05,0x07,
			0x02,0x04,0x06,0x00,0x02,0x04,0x07,0x01,0x03,0x05,0x07,0x01,0x03,0x05,0x07,0x01,0x03,0x05,0x07,0x01,0x03,0x05,0x07,
			0x01,0x03,0x05,0x06,0x00,0x02,0x04,0x06,0x00,0x02,0x03,0x05,0x07,0x01,0x02,0x04,0x06,0x00,0x02,0x03,0x05,0x07,0x00,
			0x02,0x04,0x05,0x07,0x01,0x02,0x04,0x06,0x07,0x01,0x03,0x04,0x06,0x07,0x01,0x03,0x04,0x06,0x07,0x01,0x02,0x04,0x05,
			0x07,0x00,0x02,0x03,0x05,0x06,0x00,0x01,0x03,0x04,0x06,0x07,0x01,0x02,0x04,0x05,0x06,0x00,0x01,0x03,0x04,0x05,0x07,
			0x00,0x02,0x03,0x04,0x06,0x07,0x00,0x02,0x03};

static int KTD3133_REG_RATIO_MSB_BRIGHTNESS[256] = {0x00,0x2B,0x3E,0x4B,0x55,0x5D,0x64,0x6A,0x6F,0x74,0x78,0x7C,0x7F,0x82,0x85,0x88,0x8B,
			0x8D,0x8F,0x92,0x94,0x96,0x98,0x9A,0x9B,0x9D,0x9F,0xA0,0xA2,0xA3,0xA5,0xA6,0xA7,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
			0xB1,0xB2,0xB3,0xB4,0xB5,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBC,0xBD,0xBE,0xBF,0xBF,0xC0,0xC1,0xC2,0xC2,0xC3,
			0xC4,0xC4,0xC5,0xC6,0xC6,0xC7,0xC7,0xC8,0xC9,0xC9,0xCA,0xCA,0xCB,0xCC,0xCC,0xCD,0xCD,0xCE,0xCE,0xCF,0xCF,0xD0,0xD0,
			0xD1,0xD1,0xD2,0xD2,0xD3,0xD3,0xD4,0xD4,0xD5,0xD5,0xD5,0xD6,0xD6,0xD7,0xD7,0xD8,0xD8,0xD8,0xD9,0xD9,0xDA,0xDA,0xDA,
			0xDB,0xDB,0xDC,0xDC,0xDC,0xDD,0xDD,0xDD,0xDE,0xDE,0xDF,0xDF,0xDF,0xE0,0xE0,0xE0,0xE1,0xE1,0xE1,0xE2,0xE2,0xE2,0xE3,
			0xE3,0xE3,0xE4,0xE4,0xE4,0xE5,0xE5,0xE5,0xE5,0xE6,0xE6,0xE6,0xE7,0xE7,0xE7,0xE8,0xE8,0xE8,0xE8,0xE9,0xE9,0xE9,0xE9,
			0xEA,0xEA,0xEA,0xEB,0xEB,0xEB,0xEB,0xEC,0xEC,0xEC,0xEC,0xED,0xED,0xED,0xED,0xEE,0xEE,0xEE,0xEE,0xEF,0xEF,0xEF,0xEF,
			0xF0,0xF0,0xF0,0xF0,0xF1,0xF1,0xF1,0xF1,0xF2,0xF2,0xF2,0xF2,0xF2,0xF3,0xF3,0xF3,0xF3,0xF4,0xF4,0xF4,0xF4,0xF4,0xF5,
			0xF5,0xF5,0xF5,0xF5,0xF6,0xF6,0xF6,0xF6,0xF6,0xF7,0xF7,0xF7,0xF7,0xF7,0xF8,0xF8,0xF8,0xF8,0xF8,0xF9,0xF9,0xF9,0xF9,
			0xF9,0xFA,0xFA,0xFA,0xFA,0xFA,0xFB,0xFB,0xFB,0xFB,0xFB,0xFB,0xFC,0xFC,0xFC,0xFC,0xFC,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,
			0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF};
int ktd3133_set_backlight(unsigned int bl_level);

#endif /* __LINUX_KTD3133_H */