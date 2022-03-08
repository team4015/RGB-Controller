#ifndef UART_H
#define UART_H

/* To use printf() over UART TX,
 * simply include stdio.h and call printf(); */

#define NEWLINE   "\r\n"

void uart_init(void);
void uart_transmit_byte(char byte);
char uart_receive_byte(void);
void uart_transmit(void * buffer, int size);
void uart_receive(void * buffer, int size);

#endif /* UART_H */
