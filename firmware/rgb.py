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
MIN_BRIGHTNESS = 0
MAX_BRIGHTNESS = 255

port = None

def tx_byte(byte):
	port.write(bytearray([byte]))
	port.flush()
	time.sleep(TX_DELAY)

def colour(red, green, blue):
	if red < MIN_BRIGHTNESS or red > MAX_BRIGHTNESS:
		print(f"Invalid red value '{red}'")
		return ERROR
	if green < MIN_BRIGHTNESS or green > MAX_BRIGHTNESS:
		print(f"Invalid green value '{green}'")
		return ERROR
	if blue < MIN_BRIGHTNESS or blue > MAX_BRIGHTNESS:
		print(f"Invalid blue value '{blue}'")
		return ERROR

	tx_byte(HEADER)
	tx_byte(red)
	tx_byte(green)
	tx_byte(blue)

def open():
	global port
	port = Serial(port = SERIAL_PORT, baudrate = BAUD_RATE, timeout = TIMEOUT)

def close():
	global port
	port.close()

# ================================================= #

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

	open()
	print(f"R: {red}, G: {green}, B: {blue}")
	result = colour(red, green, blue)
	close()
	return result

if __name__ == "__main__":
	exit(main(sys.argv))
