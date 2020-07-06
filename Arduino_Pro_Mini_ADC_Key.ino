#include "ADC_Key.h"

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
}

/*
 * Get a KEY_CODE from a ADC channel
 * WITH DeBouncing function
 */
static inline key getKey(int ADCPin)
{
	static volatile int a1 = 0;
	static volatile int a2 = 0;
	static volatile int a3 = 0;

	int i,j = 0;

	//Do 3 times sampling
	//1st time
	a1 = analogRead(ADCPin);
	delay(3);

	//2nd time
	a2 = analogRead(ADCPin);
	delay(3);

	//3rd time
	a3 = analogRead(ADCPin);

	//Ignore bounces
	if(abs(a1-a2) > 10 || abs(a1-a3) > 10 || abs(a2-a3) > 10){

		return KEY_NOKEY;
	}

	//put average value on a1
	a1 = (a1 + a2 + a3) / 3;

	//Trying to matching a KEY
	for(i = 0; i < ARRAY_SIZE(ADC_key_table); i++) {
		if(a1 > ADC_key_table[i][0] && a1 < ADC_key_table[i][1]) {
			//Matched a Key
			return key(i);
		}
	}

	//Didn't mach any Key
	return KEY_NOKEY;
}
	
static volatile key new_key = KEY_NOKEY;
static volatile key last_key = KEY_NOKEY;
static volatile int donot_repeat = REPEAT_DELAY;

void loop() {

	// get a new key
	new_key = getKey(ADC_CHANNEL);

	/*
	 * implement short delay before repeating keys
	 *   time             line:  ......-----------------......
	 *   long press key report:  ......K   KKKKKKKKKKKKK......
	 *   short delay  is  here:  --------^
	 */

	if(new_key != KEY_NOKEY) {
	// ^ some key pressed ^

		if(last_key != new_key){
		// ^ different key pressed as before ^

			donot_repeat = REPEAT_DELAY;
			//reporting key
			Serial.print("Report KEY");
			Serial.println(int(new_key));

		} else { 
		// ^ the same key pressed as before ^

			if(donot_repeat-- > 0){
			//^ do nothing here, let program make delay

			} else {
			// ^ delay finished, start to repeated key
				//reporting key
				Serial.print("Report KEY");
				Serial.println(int(new_key));
			}
		}


		last_key = new_key;

	} else {
	// ^ no key pressed ^

		/*
		 *   Special case e.g:   ......K K K K K ......
		 * each key press sync with sampling, but it is NOT long press,
		 * we have to report every individual key press
		 *
		 *   Every time key release, program goes to here,
		 * we reset 'donot_repeat' and 'last_key',
		 * because only key pressed and hold, we repeat key, 
		 * but if key press and release very fast,
		 * we don't count it as "hold and repeat", at least in program
		 */
		donot_repeat = REPEAT_DELAY;
		last_key = KEY_NOKEY;
	}

	delay(60);
}
