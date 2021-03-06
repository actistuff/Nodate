/*
	io.cpp - Implementation of IO module.
	
	Revision 0.
	
	Features:
			-
			
	Notes:
			-
		
	2020/09/11, Maya Posch
*/


#include <io.h>


// Static definitions.
bool stdout_active = false;
USART_devices IO::usart;

extern "C" {
	int _write(int handle, char* data, int size);
}


int _write(int handle, char* data, int size) {
	if (!stdout_active) { return 0; }
	
	int count = size;
	while (count-- > 0) {
		USART::sendUart(IO::usart, *data);
		data++;
	}
	
	return size;
}


bool IO::setStdOutTarget(USART_devices device) {
	IO::usart = device;	
	stdout_active = true;
	
	return true;
}
