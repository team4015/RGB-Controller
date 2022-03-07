# ================================================= #

CC = xc8-cc

CCFLAGS += -mcpu=16F690
CCFLAGS += -mc90lib
CCFLAGS += -mwarn=0

ART = build
EXE = rgb_controller

SRC += main.c
SRC += init.c
SRC += led.c
SRC += uart.c

HDR += pins.h
HDR += init.h
HDR += led.h
HDR += uart.h

# ================================================= #

OBJ = $(SRC:.c=.p1)

$(shell mkdir -p $(ART))

$(ART)/$(EXE): $(HDR) $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $@

clean:
	@rm -rf $(ART)

# ================================================= #
