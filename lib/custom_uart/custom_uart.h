// #ifndef UART_HAL_H
// #define UART_HAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void uart_mini_ini(uint32_t fosc, uint32_t baud);
void uart_send_c(uint8_t c);
void uart_send_str(uint8_t *str, uint8_t size);
uint16_t how_many_dig(uint16_t data);
void uart_send_uint(uint16_t data);
bool uart_alt_send_uint(uint16_t value);


//#endif