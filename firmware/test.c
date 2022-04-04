#include <stdio.h>
#include "fifo.h"

void print_fifo(FIFO * fifo)
{
	if (fifo_is_empty(fifo))
	{
		printf("EMPTY\n");
	}
	else
	{
		int current = fifo->read;

		for (int i = 0; i < fifo->length; i++)
		{
			printf("%X ", fifo->data[current]);
			current = (current + 1) % fifo->size;
		}

		printf("\n");
	}
}

int main(void)
{
	FIFO fifo;
	char buffer[3];
	fifo_init(&fifo, buffer, sizeof(buffer));
	print_fifo(&fifo);
	fifo_write_byte(&fifo, 1);
	fifo_write_byte(&fifo, 2);
	fifo_write_byte(&fifo, 3);
	fifo_write_byte(&fifo, 4);
	print_fifo(&fifo);
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	print_fifo(&fifo);
	fifo_write_byte(&fifo, 2);
	fifo_write_byte(&fifo, 3);
	printf("%X\n", fifo_read_byte(&fifo));
	fifo_write_byte(&fifo, 4);
	print_fifo(&fifo);
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	printf("%X\n", fifo_read_byte(&fifo));
	print_fifo(&fifo);
	return 0;
}
