CC=gcc
IDIR=./include
ODIR=./obj

VPATH=./src

TARGET=relaxlag

_DEPS = myfunc.h mytime.h parser.h subgrad.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o myfunc.o mytime.o parser.o subgrad.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CFLAGS=-pedantic -g -Wall -I$(IDIR)

.PHONY: all clean

all: $(TARGET)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) -o $@ $^ 

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ $(TARGET)
