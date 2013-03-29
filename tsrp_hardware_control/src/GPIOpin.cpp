#include "GPIOpin.h"

#include <string>
#include <ros/ros.h>

bool GPIOpin::io_setuped;
int  GPIOpin::mem_fd;
unsigned* GPIOpin::gpio_map;
volatile unsigned* GPIOpin::gpio;

GPIOpin::GPIOpin(unsigned int _pin, std::string _name)
{
	pin = _pin;
	name = _name;
}
GPIOpin::GPIOpin(unsigned int _pin, std::string _name, PinState _state, PinOutput _output)
{
	pin = _pin;
	name = _name;
	SetPinState(_state);
	if (_state == OUTPUT)
	{
		SetOutput(_output);
	}
}

GPIOpin::~GPIOpin() {}

bool GPIOpin::InitializeGPIOpin()
{
	return setup_io();
}

//
// Set up a memory regions to access GPIO
//
bool GPIOpin::setup_io()
{
	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
		ROS_ERROR("[GPIOpin] Cannot open /dev/mem!");
		return false;
	}

	/* mmap GPIO */
	gpio_map = (unsigned int*) mmap(
				NULL,             //Any adddress in our space will do
				BLOCK_SIZE,       //Map length
				PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
				MAP_SHARED,       //Shared with other processes
				mem_fd,           //File to map
				GPIO_BASE         //Offset to GPIO peripheral
				);

	close(mem_fd); //No need to keep mem_fd open after mmap

	if (gpio_map == MAP_FAILED) 
	{
		ROS_ERROR("[GPIOpin] mmap error %d", gpio_map); //errno also set!
		return false;
	}

	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;
	return true;
}

void GPIOpin::SetPinState(PinState _state)
{
	switch (_state)
	{
		case OUTPUT:
		{ SetAsOutput(); break; }
		case INPUT:
		{ SetAsInput(); break; }
	}
}

void GPIOpin::SetAsInput()
{
	state = INPUT;
	INP_GPIO(pin); //TODO: UNTESTED if is working
}

void GPIOpin::SetAsOutput()
{
	state = OUTPUT;
    INP_GPIO(pin); // must use INP_GPIO before we can use OUT_GPIO
    OUT_GPIO(pin);
}

void GPIOpin::ToggleOutput()
{
	output = (output == LOW)?(HIGH):(LOW);
	SetOutput(output);
}

void GPIOpin::SetOutput(PinOutput _output)
{
	output = _output;
	switch(_output)
	{
		case HIGH:
		{
			GPIO_SET = 1<<pin;
			break;
		}
		case LOW:
		{
			GPIO_CLR = 1<<pin;
			break;
		}
	}
}
