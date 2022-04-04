import rgb

port = rgb.open()

rgb.colour(0, 0, 0)

red = rgb.MAX_BRIGHTNESS
green = 0
blue = 0

def update():
    rgb.colour(red, green ,blue)

while green < rgb.MAX_BRIGHTNESS:
    update()
    green = green + 1

while red > rgb.MIN_BRIGHTNESS:
    update()
    red = red - 1

while blue < rgb.MAX_BRIGHTNESS:
    update()
    blue = blue + 1

while green > rgb.MIN_BRIGHTNESS:
    update()
    green = green - 1

while red < rgb.MAX_BRIGHTNESS:
    update()
    red = red + 1

while blue > rgb.MIN_BRIGHTNESS:
    update()
    blue = blue - 1

rgb.close()
