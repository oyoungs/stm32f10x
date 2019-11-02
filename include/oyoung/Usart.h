/*
 * Usart.h
 *
 *  Created on: 2019Äê4ÔÂ21ÈÕ
 *      Author: Oyoung
 */

#ifndef USART_H_
#define USART_H_

#include <stddef.h>

namespace oyoung {


class Usart {
public:
	enum class Parity {
		none,
		odd,
		even
	};
public:
	Usart();
	explicit Usart(int id, unsigned databits = 8, unsigned stopbits = 1, Parity parity = Parity::none);

	unsigned baudrate() const;
	Usart& baudrate(unsigned baud);

	unsigned databits() const;
	Usart& databits(unsigned databits);

	unsigned stopbits() const;
	Usart& stopbits(unsigned stopbits);

	Parity parity() const;
	Usart& parity(Parity parity);


	void flush();

	void enable(bool yes = true);
	void disable(bool yes = true);

	int send(const char *messgae);

	int write(const void *data, size_t size);

	int read(void *data, size_t size);

	~Usart();

private:

	struct UsartInfo {
		int id{0};
		unsigned baudrate {115200};
		unsigned databits{8};
		unsigned stopbits{1};
		Parity parity{Parity::none};

		UsartInfo() {}

		UsartInfo(int id, unsigned  baudrate, unsigned databits, unsigned stopbits, Parity parity)
			: id(id), baudrate(baudrate), databits(databits), stopbits(stopbits), parity(parity){

		}
	} m_info;
};

} /* namespace oyoung */

#endif /* USART_H_ */
