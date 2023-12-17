CC = g++
CFLAGS = -Wall -lopengl32 -lglu32 -lgdi32 -luser32 -lmingw32
SRCS = main.cpp xkwindow.hpp
TARGET = open.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean