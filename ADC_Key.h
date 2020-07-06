#ifndef ADC_KEY_H
#define ADC_KEY_H

#define ADC_CHANNEL A7
#define REPEAT_DELAY 10

#define ARRAY_SIZE(array) \
	(sizeof(array) / sizeof(array[0]))

const int ADC_key_table[5][2] = {
	{0x2a5, 0x2af},		//KEY 0 ADC Value
	{0x120, 0x140}, 	//KEY 1 ADC Value
	{0x210, 0x220}, 	//KEY 2 ADC Value
	{0x280, 0x290}, 	//KEY 3 ADC Value
	{0x2E0, 0x2E5}  	//KEY 4 ADC Value
};

typedef enum {
	KEY_MIDDLE = 0,		//KEY 0
	KEY_LEFT,		//KEY 1
	KEY_RIGHT,		//KEY 2
	KEY_DOWN,		//KEY 3
	KEY_ROTATE,		//KEY 4
	KEY_NOKEY
} key;

#endif

