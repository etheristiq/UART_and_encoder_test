#include "custom_timer.h"
#include <avr/interrupt.h>

/*
    UInt8 - [ 0 : 255 ]
    UInt16 - [ 0 : 65535 ]
    UInt32 - [ 0 : 4294967295 ]           //переполнение tiki случается каждые 49.7 дня.
    UInt64 - [ 0 : 18446744073709551615 ]
*/
volatile uint32_t tiki;                   //Можно поставить uint64_t хватит на пару тысячелетий)

ISR(TIMER0_OVF_vect) {
	tiki++;
	TCNT0=6;// 256-(16000000/64)/1000=6
}

// инициализация таймера T0 на прерывание каждые 1 мс.
void G_timer_ini(void) {
	TCCR0B|=(1<<CS01)|(1<<CS00); // делитеь 64
	TIMSK0|=(1<<TOIE0); // включить прерывание по переполнению
	TCNT0=6;// 256-(16000000/64)/1000=6; если значение TCNT0=6 то прошла 1 мс
}

uint32_t millis(void) {
	return tiki;
}