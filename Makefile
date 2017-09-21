CC=gcc
CFLAGS=-O3
hangul.so: lua_hangul.c
	$(CC) $(CFLAGS) $^ -o $@ -I /usr/include/hangul-1.0 -l hangul -fPIC -shared
n
