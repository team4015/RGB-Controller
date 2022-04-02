import rgb

port = rgb.open_port()

rgb.rgb(port, 0, 0, 0)

red = 255
green = 0
blue = 0

def update():
    rgb.rgb(port, red, green ,blue)

while green < 255:
    update()
    green = green + 1

while red > 0:
    update()
    red = red - 1

while blue < 255:
    update()
    blue = blue + 1

while green > 0:
    update()
    green = green - 1

while red < 255:
    update()
    red = red + 1

while blue > 0:
    update()
    blue = blue - 1

port.close