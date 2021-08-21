TARGET=gnuapi
LIBS=web-scraping/scraping.c
CC=gcc
CFLAGS= -pedantic -Wall

.PHONY: default all clone

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

clone:
	git clone https://github.com/leozamboni/web-scraping

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean: 
	-rm -f *.o
	-rm -f *.tmp
	-rm -fr web-scraping
	-rm -f $(TARGET)
