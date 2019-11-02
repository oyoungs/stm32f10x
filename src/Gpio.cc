/*
 * Gpio.cpp
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#include <oyoung/Gpio.h>
#include <stm32f10x_gpio.h>

namespace oyoung {

static GPIO_TypeDef * const gpio_map[] = {
	GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG
};
uint16_t GPIO_Pin(Gpio::Pin pin) {
	return static_cast<uint16_t>(pin);
}

GPIOMode_TypeDef GPIO_Mode(Gpio::Mode mode) {
	return static_cast<GPIOMode_TypeDef>(mode);
}

GPIOSpeed_TypeDef GPIO_Speed(Gpio::Speed speed) {
	return static_cast<GPIOSpeed_TypeDef>(speed);
}


Gpio::Gpio(Gpio::Port port, Gpio::Pin pin, Gpio::Mode mode, Gpio::Speed speed)
	: m_info(port, pin, mode, speed)  {

}

Gpio& Gpio::mode(Gpio::Mode gmode) {
	m_info.mode = gmode;
	return *this;
}

Gpio& Gpio::speed(Gpio::Speed gspeed)  {
	m_info.speed = gspeed;
	return *this;
}

void Gpio::output(bool bit) {
	GPIO_WriteBit(gpio_map[m_info.port], GPIO_Pin(m_info.pin), bit ? Bit_SET : Bit_RESET);
}

unsigned Gpio::input() const {
	return GPIO_ReadInputData(gpio_map[m_info.port]) & GPIO_Pin(m_info.pin);
}

unsigned Gpio::output() const {
	return GPIO_ReadOutputData(gpio_map[m_info.port]) & GPIO_Pin(m_info.pin);
}

void Gpio::flush() {

	GPIO_InitTypeDef init{};


	init.GPIO_Pin = GPIO_Pin(m_info.pin);
	init.GPIO_Mode = GPIO_Mode(m_info.mode);
	init.GPIO_Speed = GPIO_Speed(m_info.speed);

	GPIO_Init(gpio_map[m_info.port], &init);

}


Gpio::~Gpio() {

}

} /* namespace oyoung */
