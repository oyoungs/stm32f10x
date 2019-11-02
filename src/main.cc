//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------


#include <oyoung/Rcc.h>
#include <oyoung/Gpio.h>
#include <oyoung/Usart.h>
#include <oyoung/Systick.h>

#include <stm32f10x.h>

using namespace oyoung;
using namespace oyoung::rcc;

int main(int, char**)
{

	SystemInit();

	auto& systick = Systick::shared(72);

	APB2Periph(APB2Periph::Clock::usart1
			| APB2Periph::Clock::gpioa
			| APB2Periph::Clock::gpioc
			| APB2Periph::Clock::gpiod
			| APB2Periph::Clock::afio).enable();

	Gpio(Gpio::Port::A, Gpio::Pin::_9, Gpio::Mode::af_push_pull, Gpio::Speed::_50Mhz).flush();
	Gpio(Gpio::Port::A, Gpio::Pin::_10, Gpio::Mode::input_floating, Gpio::Speed::_50Mhz).flush();

	Gpio led1(Gpio::Port::C, Gpio::Pin::_3, Gpio::Mode::output_push_pull, Gpio::Speed::_50Mhz);
	Gpio led2(Gpio::Port::D, Gpio::Pin::_6, Gpio::Mode::output_push_pull, Gpio::Speed::_50Mhz);

	Usart serial(0);

	serial.baudrate(9600)
		  .databits(8)
		  .stopbits(0x10)
		  .flush();

	serial.enable();

	led1.flush();
	led2.flush();

	led1.output(1);
	led2.output(0);

	int ledOn = 1;


	while (true)
	{
	   serial.send("Hello, World\n");
	   led1.output(ledOn);
	   ledOn = !ledOn;
	   led2.output(ledOn);
	   systick.sleep_ms(1000);

	}

	return 0;
}


// ----------------------------------------------------------------------------
