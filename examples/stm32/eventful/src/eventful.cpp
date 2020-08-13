// Basic Event example for Nodate's STM32 framework.

#include <gpio.h>
#include <interrupts.h>


volatile bool led_on;


void callBack_A() {
	if (led_on) { led_on = false; }
	else { led_on = true; }
}


void callBack_B() {
	if (led_on) { led_on = false; }
	else { led_on = true; }
}


int main () {
	// Initialise.
	GPIO gpio;
	Interrupts itrs;
	
	// FIXME: Dynamically updated LED_BUILTIN value.
	uint8_t LED_BUILTIN = 3;
	
	// Set the pin mode on the built-in LED.
	gpio.set_output(GPIO_PORT_B, LED_BUILTIN, GPIO_PULL_UP);
	gpio.write(GPIO_PORT_B, LED_BUILTIN, GPIO_LEVEL_LOW);
	
	// Set the interrupts for the rotary encoder.
	// A: Port B, pin 0 (D3 on Nucleo-32).
	// B: Port B, pin 1 (D6 on Nucleo-32).
	uint8_t handleA, handleB;
	itrs.setInterrupt(0, GPIO_PORT_B, INTERRUPT_TRIGGER_FALLING, callBack_A, 0, handleA);
	itrs.setInterrupt(1, GPIO_PORT_B, INTERRUPT_TRIGGER_FALLING, callBack_B, 0, handleB);
	
	while (1) {
		if (led_on) {
			gpio.write(GPIO_PORT_B, LED_BUILTIN, GPIO_LEVEL_HIGH);
		}
		else {
			gpio.write(GPIO_PORT_B, LED_BUILTIN, GPIO_LEVEL_LOW);
		}
	}
	
	return 0;
}