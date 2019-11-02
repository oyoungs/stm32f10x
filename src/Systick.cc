/*
 * Systick.cc
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#include <oyoung/Systick.h>

#include <misc.h>
#include <CMSIS/core_cm3.h>

namespace oyoung {

Systick::Systick(unsigned sysclock)
	: m_factor(sysclock >> 3, (sysclock >> 3) * 1000) {
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

Systick::~Systick() {
	// TODO Auto-generated destructor stub
}

Systick& Systick::shared(unsigned sysclock) {
	static Systick systick(sysclock);
	return systick;
}


Systick& Systick::sleep_us(unsigned microseconds) {

	SysTick->LOAD = microseconds * m_factor.microseconds;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
	uint32_t temp = SysTick->CTRL;
	while((temp & 0x01) != 0 && (temp & 0x10000) == 0) {
		temp = SysTick->CTRL;
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0X00;
	return *this;
}

Systick& Systick::sleep_ms(unsigned milliseconds) {
	while(milliseconds --) sleep_us(1000);
	return *this;
}


} /* namespace oyoung */
