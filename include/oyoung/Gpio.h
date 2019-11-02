/*
 * Gpio.h
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#ifndef GPIO_H_
#define GPIO_H_

namespace oyoung {

class Gpio {

public:
	enum class Port {
		A,B,C,D,E,F,G
	};

	enum Pin {
		none,
		_0 = 0x01, _1 = 0x02, _2 = 0x04, _3 = 0x08, _4 = 0x10, _5 = 0x20, _6 = 0x40, _7 = 0x80,
		_8 = 0x0100, _9 = 0x0200, _10 = 0x0400, _11 = 0x0800, _12 = 0x1000, _13 = 0x2000, _14 = 0x4000, _15 = 0x8000,
		low = 0xff,
		high = 0xff00,
		all = 0xffff
	};

	enum class Mode {

		input_anolog = 0x0,
		input_floating = 0x04,
		input_pull_down = 0x28,
		input_pull_up = 0x48,
		output_open_drain = 0x14,
		output_push_pull = 0x10,
		af_open_drain = 0x1C,
		af_push_pull = 0x18
	};

	enum class Speed {
		_10Mhz = 1,
		_2Mhz,
		_50Mhz
	};

public:
	Gpio(Port port, Pin pin, Mode mode, Speed speed);

	Gpio& mode(Mode m);

	Gpio& speed(Speed s);

	void output(bool bit);

	unsigned input() const;

	unsigned output() const;

	void flush();

	~Gpio();

private:
	struct GpioInfo {
		int port;
		Pin pin;
		Mode mode;
		Speed speed;
		GpioInfo(Port port, Pin pin, Mode mode, Speed speed)
			: port(static_cast<int>(port)), pin(pin), mode(mode), speed(speed) {

		}
	} m_info;

};

} /* namespace oyoung */

#endif /* GPIO_H_ */
