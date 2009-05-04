CC=gcc
IDIR=./include
ODIR=./obj

VPATH=./src

TARGET=relaxlag

_DEPS = edgefunc.h mytime.h parser.h lagrel.h rlfunc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o edgefunc.o mytime.o parser.o lagrel.o rlfunc.o
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
