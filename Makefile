CC=gcc
CFLAGS=-O3
build/hangul.so: lua_hangul.c
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ -I /usr/include/hangul-1.0 -l hangul -fPIC -shared
all: build/hangul.so
clean:
	rm -rf build
