TARGET=newt
TARGET_SO=newt.so
LIBS=
CC=gcc
CFLAGS=-g -Wall -I. -fsigned-char -fPIC -D__LINUX__
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS_SO += $(filter-out main.o,$(OBJECTS))	
HEADERS = $(wildcard *.h)

default: $(TARGET) $(TARGET_SO)

# Link executable
$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

# Link shared library
$(TARGET_SO) : $(OBJECTS_SO)
	$(CC) $(OBJECTS_SO) -Wall -shared $(LIBS) -o $@


# Compile
%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	-rm -f *.o
	-rm -f $(TARGET)
