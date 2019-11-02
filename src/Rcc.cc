/*
 * Rcc.cc
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#include <oyoung/Rcc.h>
#include <stm32f10x_rcc.h>

namespace oyoung {
namespace rcc {

	APB2Periph::APB2Periph(unsigned clock)
		: m_info(clock) {

	}

	void APB2Periph::enable(bool yes) {
		RCC_APB2PeriphClockCmd(m_info.clock, yes ? ENABLE: DISABLE);
	}

	void APB2Periph::disable(bool yes) {
		RCC_APB2PeriphClockCmd(m_info.clock, yes ? DISABLE: ENABLE);
	}

} /* namespace rcc*/
} /* namespace oyoung */
