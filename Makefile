CFLAGS +=\
	-std=c89\
	-Wall\
	-Wextra\
	-Wpedantic
BITS := $(shell uname -a | grep -Po '(?<=MINGW)\d+')

all:
	$(CC) -fPIC -shared $(CFLAGS) -DBITS=\"$(BITS)\" -o dark$(BITS).dll -ldwmapi dark.c
	$(CC) $(CFLAGS) -DBITS=\"$(BITS)\" -o dark$(BITS) $(LDFLAGS) main.c
