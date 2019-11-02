/*
 * Usart.cc
 *
 *  Created on: 2019Äê4ÔÂ21ÈÕ
 *      Author: Oyoung
 */

#include <oyoung/Usart.h>
#include <stm32f10x.h>

#include <string.h>

namespace oyoung {

uint16_t USART_WordLength(unsigned databits)
{
	if(databits == 9) {
		return USART_WordLength_9b;
	}
	return USART_WordLength_8b;
}

uint16_t USART_StopBits(unsigned stopbits)
{
	switch(stopbits) {
	case 0x05:
		return USART_StopBits_0_5;
	case 0x10:
		return USART_StopBits_1;
	case 0x15:
		return USART_StopBits_1_5;
	case 0x20:
		return USART_StopBits_2;
	default:
		break;
	}
	return USART_StopBits_1;
}

uint16_t USART_Parity(Usart::Parity parity)
{
	switch(parity) {
		case Usart::Parity::none:
			return USART_Parity_No;
		case Usart::Parity::odd:
			return USART_Parity_Odd;
		case Usart::Parity::even:
			return USART_Parity_Even;
	}
	return USART_Parity_No;
}

static USART_TypeDef * const usart_map[] = {
		USART1,
		USART2,
		USART3,
		UART4,
		UART5
};

static IRQn_Type const usart_irq[] = {
		USART1_IRQn,
		USART2_IRQn,
		USART3_IRQn,
		UART4_IRQn,
		UART5_IRQn
};


Usart::Usart() {
}

Usart::Usart(int id, unsigned databits , unsigned stopbits, Parity parity )
	: m_info(id, 115200, databits, stopbits, parity) {
}

Usart::~Usart() {
}

unsigned Usart::baudrate() const {
	return m_info.baudrate;
}

Usart& Usart::baudrate(unsigned baud) {
	m_info.baudrate = baud;
	return *this;
}

unsigned Usart::databits() const {
	return m_info.databits;
}

Usart& Usart::databits(unsigned databits) {
	m_info.databits = databits;
	return *this;
}

unsigned Usart::stopbits() const {
	return m_info.stopbits;
}

Usart& Usart::stopbits(unsigned stopbits)
{
	m_info.stopbits = stopbits;
	return *this;
}

Usart::Parity Usart::parity() const {
	return m_info.parity;
}

Usart& Usart::parity(Usart::Parity parity)
{
	m_info.parity = parity;
	return *this;
}

void Usart::flush() {

	USART_InitTypeDef init;
	NVIC_InitTypeDef nvic;
	init.USART_BaudRate = m_info.baudrate;
	init.USART_WordLength = USART_WordLength(m_info.databits);
	init.USART_StopBits = USART_StopBits(m_info.stopbits);
	init.USART_Parity = USART_Parity(m_info.parity);
	init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(usart_map[m_info.id], &init);

	nvic.NVIC_IRQChannel = usart_irq[m_info.id];
	nvic.NVIC_IRQChannelPreemptionPriority=3 ;
	nvic.NVIC_IRQChannelSubPriority = 3;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
    USART_ITConfig(usart_map[m_info.id], USART_IT_RXNE, ENABLE);
}

void Usart::enable(bool yes)
{
	USART_Cmd(usart_map[m_info.id], yes ? ENABLE: DISABLE);
}

void Usart::disable(bool yes)
{
	USART_Cmd(usart_map[m_info.id], yes ? DISABLE: ENABLE);
}

int Usart::send(const char *message)
{
	return write(message, strlen(message));
}

int Usart::write(const void *data, size_t size)
{
	uint16_t byte = 0;
	for(auto i = 0u; i < size; ++i) {
		while((usart_map[m_info.id]->SR & 0X40) == 0);
		byte = *((uint8_t *)data + i);
		USART_SendData(usart_map[m_info.id], byte);
	}
	return size;
}

} /* namespace oyoung */
