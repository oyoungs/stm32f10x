/*
 * Systick.h
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include <chrono>

namespace oyoung {

class Systick {
public:

	static Systick& shared(unsigned sysclock = 0);

public:
	Systick(unsigned sysclock);

	Systick& sleep_us(unsigned microseconds);

	Systick& sleep_ms(unsigned milliseconds);

	void tick();

	~Systick();

private:
	struct Factor {
		uint8_t milliseconds;
		uint16_t microseconds;

		Factor(int micro, int milli)
			: milliseconds(milli), microseconds(micro) {

		}

	} m_factor;

	struct Tick {
		unsigned seconds{0};
		unsigned milliseconds{0};
		unsigned microseconds{0};

		void add(unsigned micro) {
			microseconds += micro;

			while(microseconds > 1000) {
				milliseconds++;
				microseconds -= 1000;
			}

			while(milliseconds > 1000) {
				seconds++;
				milliseconds -= 1000;
			}
		}

	} m_tick;
};


} /* namespace oyoung */

#endif /* SYSTICK_H_ */
