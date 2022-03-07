#ifndef UART_H
#define UART_H

/* To use printf() over UART TX,
 * simply include stdio.h and call printf(); */

#define NEWLINE   "\r\n"

void uart_init(void);
void uart_transmit_byte(char byte);
char uart_receive_byte(void);
int uart_transmit(void * buffer, int size);
int uart_receive(void * buffer, int size);
void uart_echo(void);
//int uart_transmit_message(Message message);
//Message uart_receive_message(void);

#endif /* UART_H */
