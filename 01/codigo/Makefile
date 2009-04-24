CC=gcc
IDIR=./include
ODIR=./obj

VPATH=./src

TARGET=relaxlag

_DEPS = parser.h mytime.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = parser.o mytime.o main.o 
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

run: $(TARGET)
	./$(TARGET) 1 ../../RL-instances/v10_d50.dat
