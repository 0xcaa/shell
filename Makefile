CFILES = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
PREFIX=/usr/local

CC=gcc
####LDFLAGS = -lb64
CFLAGS= -c $(LDFLAGS) -g -Wall -pedantic

shell: $(OBJFILES)
	$(CC) -o $@ $^

.PHONY:clean
clean:
	rm -f $(OBJFILES) shell
install:
	cp cipherinfo $(DESTDIR)$(PREFIX)/bin/cipherinfo
uninstall:
	rm cipherinfo $(DESTDIR)$(PREFIX)/bin/cipherinfo

