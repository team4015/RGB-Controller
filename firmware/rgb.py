import sys
import time

from serial import Serial

ERROR = -1
SUCCESS = 0

SERIAL_PORT = "/dev/cu.usbserial-AQ00PEW7"
BAUD_RATE = 9600
HEADER = 0xFF
TX_DELAY = 1.5e-3  # 1.5 ms
TIMEOUT = 1        # 1s

def tx_byte(port, byte):
	port.write(bytearray([byte]))
	port.flush()
	time.sleep(TX_DELAY)

def rgb(port, red, green, blue):
	tx_byte(port, HEADER)
	tx_byte(port, red)
	tx_byte(port, green)
	tx_byte(port, blue)

def open_port():
	return Serial(port = SERIAL_PORT, baudrate = BAUD_RATE, timeout = TIMEOUT)

def sweep(port):
	for i in range(256):
		rgb(port, 0, 0, i)

MIN_ARGC = 4
MAX_ARGC = 5

def main(argv):
	argc = len(argv)
	if argc < MIN_ARGC or argc > MAX_ARGC:
		print("Incorrect arguments")
		return ERROR

	red = int(argv[1])
	green = int(argv[2])
	blue = int(argv[3])
	loop = 0

	if (argc == 5):
		loop = int(argv[4])

	port = open_port()

	while (1):
		print(f"R: {red}, G: {green}, B: {blue}")
		rgb(port, red, green, blue)
		if (loop == 0):
			break

	# sweep(port)
	port.close()

	return SUCCESS

if __name__ == "__main__":
	exit(main(sys.argv))
