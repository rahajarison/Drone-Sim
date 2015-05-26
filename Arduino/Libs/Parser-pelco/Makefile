CC=			g++
CFLAGS=		-Wall
SRC=		PelcoMessage.cpp main.cpp PelcoBuffer.cpp Arduino.cpp
OBJ=		$(SRC:.cpp=.o)
TARGET=		parser.exe

all:		$(SRC) $(TARGET)

$(TARGET):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm $(OBJ)

fclean: clean
	rm $(TARGET)

re: fclean all
