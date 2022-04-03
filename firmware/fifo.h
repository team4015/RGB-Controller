/* =================================================
 * Circular FIFO buffer.  Each each element is 1 B.
 * ================================================= */

#ifndef FIFO_H
#define FIFO_H

#include <stdbool.h>

struct FIFO
{
	char * data;
	int read;
	int write;
	int size;
	int length;
};

typedef struct FIFO FIFO;

void fifo_init(FIFO * fifo, char * buffer, int size);
void fifo_reset(FIFO * fifo);
char fifo_read_byte(FIFO * fifo);
void fifo_write_byte(FIFO * fifo, char value);
bool fifo_is_full(FIFO * fifo);
bool fifo_is_empty(FIFO * fifo);

#endif /* FIFO_H */
