#ifndef ADC_KEY_H
#define ADC_KEY_H

#define ADC_CHANNEL A7
#define REPEAT_DELAY 10

#define ARRAY_SIZE(array) \
	(sizeof(array) / sizeof(array[0]))

const int ADC_key_table[5][2] = {
	{0x2a5, 0x2af},		//0 KEY_MIDDLE 1
	{0x120, 0x140}, 	//1 KEY_LEFT 2
	{0x210, 0x220}, 	//2 KEY_RIGHT 3
	{0x280, 0x290}, 	//3 KEY_DOWN 4
	{0x2E0, 0x2E5}  	//4 KEY_ROTATE 5
};

typedef enum {
	KEY_MIDDLE = 0,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_ROTATE,
	KEY_NOKEY
} key;

#endif

