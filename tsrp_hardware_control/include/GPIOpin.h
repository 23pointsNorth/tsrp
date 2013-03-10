#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

enum PinOutput {HIGH, LOW};
enum PinState {INPUT, OUTPUT};

class GPIOpin
{
public:
	GPIOpin(unsigned int _pin, std::string _name);
	GPIOpin(unsigned int _pin, std::string _name, PinState _state, PinOutput _output = LOW);
	~GPIOpin();

	void SetPinState(PinState _state);
	void SetAsInput();
	void SetAsOutput();
	void SetOutput(PinOutput _output);
	void ToggleOutput();

	static bool InitializeGPIOpin();

private:
	unsigned int pin;
	std::string name;
	PinState state;
	PinOutput output;

	static bool io_setuped;
	static bool setup_io();

	static int  mem_fd;
	static unsigned* gpio_map;

	// I/O access
	static volatile unsigned *gpio;
};

#endif /* GPIOPIN_H_ */