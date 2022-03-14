import sys
import time

from serial import Serial

ERROR = -1
SUCCESS = 0

SERIAL_PORT = "/dev/cu.usbserial-AQ00PEW7"
BAUD_RATE = 9600
HEADER = 0xFF
TX_DELAY = 10e-3   # 10 ms
TIMEOUT = 1        # 1s

def tx_byte(port, byte):
	port.write(bytearray([byte]))
	port.flushOutput()
	time.sleep(TX_DELAY)

def rgb(port, red, green, blue):
	print(f"R: {red}, G: {green}, B: {blue}")
	tx_byte(port, HEADER)
	tx_byte(port, red)
	tx_byte(port, green)
	tx_byte(port, blue)

MIN_ARGC = 4
MAX_ARGC = 4

def main(argv):
	argc = len(argv)
	if argc < MIN_ARGC or argc > MAX_ARGC:
		print("Incorrect arguments")
		return ERROR

	red = int(argv[1])
	green = int(argv[2])
	blue = int(argv[3])

	port = Serial(port = SERIAL_PORT, baudrate = BAUD_RATE, timeout = TIMEOUT)
	rgb(port, red, green, blue)
	port.close()

	return SUCCESS

exit(main(sys.argv))
