#include "fifo.h"

#include <stddef.h>

void fifo_init(FIFO * fifo, char * buffer, int size)
{
	if (fifo == NULL || buffer == NULL || size < 1)
	{
		return;
	}

	fifo->data = buffer;
	fifo->size = size;
	fifo_reset(fifo);
}

void fifo_reset(FIFO * fifo)
{
	if (fifo == NULL)
	{
		return;
	}

	fifo->length = 0;
	fifo->read = 0;
	fifo->write = 0;
}

char fifo_read_byte(FIFO * fifo)
{
	if (fifo == NULL || fifo_is_empty(fifo))
	{
		return 0;
	}

	char value = fifo->data[fifo->read];
	fifo->read = (fifo->read + 1) % fifo->size;
	fifo->length--;
	return value;
}

void fifo_write_byte(FIFO * fifo, char value)
{
	if (fifo == NULL || fifo_is_full(fifo))
	{
		return;
	}

	fifo->data[fifo->write] = value;
	fifo->write = (fifo->write + 1) % fifo->size;
	fifo->length++;
}

bool fifo_is_full(FIFO * fifo)
{
	if (fifo == NULL)
	{
		return false;
	}

	return fifo->length == fifo->size;
}

bool fifo_is_empty(FIFO * fifo)
{
	if (fifo == NULL)
	{
		return false;
	}

	return fifo->length == 0;
}
