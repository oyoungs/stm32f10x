/*
 * Rcc.h
 *
 *  Created on: 2019Äê11ÔÂ2ÈÕ
 *      Author: Oyoung
 */

#ifndef RCC_H_
#define RCC_H_

namespace oyoung {
namespace rcc {

class APB2Periph {
public:

	/*
#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2Periph_GPIOE             ((uint32_t)0x00000040)
#define RCC_APB2Periph_GPIOF             ((uint32_t)0x00000080)
#define RCC_APB2Periph_GPIOG             ((uint32_t)0x00000100)
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000200)
#define RCC_APB2Periph_ADC2              ((uint32_t)0x00000400)
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2Periph_TIM8              ((uint32_t)0x00002000)
#define RCC_APB2Periph_USART1            ((uint32_t)0x00004000)
#define RCC_APB2Periph_ADC3              ((uint32_t)0x00008000)
#define RCC_APB2Periph_TIM15             ((uint32_t)0x00010000)
#define RCC_APB2Periph_TIM16             ((uint32_t)0x00020000)
#define RCC_APB2Periph_TIM17             ((uint32_t)0x00040000)
#define RCC_APB2Periph_TIM9              ((uint32_t)0x00080000)
#define RCC_APB2Periph_TIM10             ((uint32_t)0x00100000)
#define RCC_APB2Periph_TIM11             ((uint32_t)0x00200000)
	 * */

	enum Clock {
		 afio = 0x01,
		 gpioa = 0x04, gpiob = 0x08, gpioc = 0x10, gpiod = 0x20, gpioe = 0x40, gpiof = 0x80, gpiog = 0x100,
		 adc1 = 0x200, adc2 = 0x400,
		 timer1 = 0x800,
		 spi1 = 0x1000,
		 timer8 = 0x2000,
		 usart1 = 0x4000,
		 adc3 = 0x8000,
		 timer15 = 0x10000, timer16 = 0x20000, timer17 = 0x40000, timer9 = 0x80000, timer10 = 0x100000, timer11 = 0x200000
	};

	APB2Periph(unsigned clock);

	void enable(bool yes = true);
	void disable(bool yes = true);

private:
	struct ClockInfo {
		unsigned clock{0};
		ClockInfo(unsigned clock)
			: clock(clock) {

		}
	} m_info;
};


} /* namespace rcc */
} /* namespace oyoung */

#endif /* RCC_H_ */
