TARGET=gnuapi
LIBS=web-scraping/scraping.c
CC=gcc
CFLAGS= -pedantic -Wall

.PHONY: default all

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	git clone https://github.com/leozamboni/web-scraping & $(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@


clean: 
	-rm -f *.o
	-rm -f *.tmp
	-rm -r web-scraping
	-rm -f $(TARGET)
