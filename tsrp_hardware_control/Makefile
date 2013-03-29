CC = g++
CFLAGS 	= -c -Wall -O3 -fPIC -I ./include/ 
LDFLAGS = -shared

SOURCES		= $(wildcard ./src/*.cpp)

OBJECTS		= $(SOURCES:.cpp=.o)

LIBRARY 	= libtsrp_hardware_control.so

all: $(SOURCES) $(LIBRARY)
	
$(LIBRARY): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CURDIR)/$< -o $@

clean: 
	rm -rf ./src/*.o $(LIBRARY)

