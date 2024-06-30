CFLAGS +=\
	-std=c89\
	-Wall\
	-Wextra\
	-Wpedantic

all:
	$(CC) -fPIC -shared $(CFLAGS) -o dark.dll -ldwmapi dark.c
	$(CC) $(CFLAGS) -o dark $(LDFLAGS) main.c
