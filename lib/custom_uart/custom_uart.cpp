#include "custom_uart.h"

// #define FOSC 16000000
// #define BAUD 9600


void uart_mini_ini(uint32_t fosc, uint32_t baud){
    
    UCSR0C &= ~(1<<USBS0);//на всякий случай перестрахуемся (ставим 1 стоп бит)

    /*Set baud rate */
    UBRR0H = (unsigned char) ((fosc/16/baud-1)>>8);
    UBRR0L = (unsigned char) (fosc/16/baud-1);
    
    //UCSR0A |= (1<<U2X0);              //speed x2 - ON
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);   //включаем передачу и приём
    UCSR0C = (3<<UCSZ00);               // 3 = 011 UCSZn2-UCSZn1-UCSZn0 одно целое

}

void uart_send_c(uint8_t c){
    while (!(UCSR0A & (1<<UDRE0))); //Ждём когда очистится буфер передачи
    UDR0 = c;
}

// void uart_send_str(uint8_t* str){     //строчка должна заканчиваться NULL'ом
//   while(*str > 0) uart_send_c(*str++);//в конце отправится лишний символ
// }

void uart_send_str(uint8_t *str, uint8_t size){
  for (int8_t i=0; i<size; i++){
    uart_send_c(str[i]);
  }
}

uint16_t how_many_dig(uint16_t data){
    uint16_t i =0;

    for(; data>0; i++)
      data/=10;
    
    return i;
}

void uart_send_uint(uint16_t data){ //так как дисплей может выводить не больше 4 цифр, ограничимся 10^4

  //48='0', 57 = '9'

  uart_send_c((uint8_t) 48+data/1000);
  uart_send_c((uint8_t) 48+data/100-data/1000*10);
  uart_send_c((uint8_t) 48+data/10-data/100*10);
  uart_send_c((uint8_t) 48+data-data/10*10);

}

bool uart_alt_send_uint(uint16_t value){//альтернативный способ формирования 4х значного числа
                                        //

	if (value > 9999) return false;	

	uint8_t digits[4];
  
	digits[0] = (int)value / 1000;      	// количесто тысяч в числе
	uint16_t b = (int)digits[0] * 1000; 	// вспомогательная переменная
	digits[1] = ((int)value - b) / 100; 	// получем количество сотен
	b += digits[1] * 100;               	// суммируем сотни и тысячи
	digits[2] = (int)(value - b) / 10;  	// получем десятки
	b += digits[2] * 10;                	// сумма тысяч, сотен и десятков
	digits[3] = value - b;              	// получаем количество единиц
	
  return false;
}