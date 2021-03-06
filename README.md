# RGB Controller
Hardware and firmware for controlling LED RGB strips on FRC robots.

## Protocol

The RGB Controller circuit board contains a PIC16F690 microcontroller that sets the RGB colour using PWM signals.  The PIC runs the C firmware found in the `firmware` folder.  The RoboRIO can talk to the PIC using the following specific protocol:

By default, the PIC waits for the byte `0xFF` on its RX line.  Any other bytes will be discarded.  Once the PIC receives the `0xFF` header byte, it will receive three more bytes from the RX line.  These three bytes are used as the RGB brightness values.  Therefore, so set the RGB colour, the RoboRIO must send a total of 4 bytes:

```python
header = 0xFF

# RGB values must be between 0 and 255
red = 128
green = 255
blue = 0

packet = [header, red, green, blue]
send(packet)
```

**NOTE:** The PIC will never respond to the RoboRIO by sending back data.  Lights are a non-critical feature of the robot so the RoboRIO should not sit around waiting for the PIC to respond.

# Serial Port

The PIC communicates with the RoboRIO over UART, using only the TX and RX lines.  You will also need to connect the GND lines between the RGB controller board and the serial port on the RoboRIO.  The baud rate must be `9600` bps (the exact baud rate is `9615` if you want to be super precise).  No parity bits are used.  The size of one byte must be 8 bits.

**IMPORTANT:**  The PIC cannot receive more than one byte at a time.  Therefore, make sure that the RoboRIO sends data one byte at a time, with a delay of 1.5 ms between each byte.  It is advised to flush the serial port TX buffer after writing each byte.  See the Python script `rgb.py` under `firmware` for an example.

# Python Test Scripts

There are two Python test scripts: `rgb.py` and `rainbow.py`.  `rgb.py` is used to set a specific RGB colour once.  `rainbow.py` will run through the colour spectrum.

First install `pyserial`:
```
pip3 install pyserial
```

To run `rgb.py`:
```
python3 rgb.py <red> <green> <blue>
```
`red`, `green`, and `blue` must be values from `0` to `255`.

To run `rainbow.py`:
```
python3 rainbow.py
```
