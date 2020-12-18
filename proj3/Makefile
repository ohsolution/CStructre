# Makefile

COMP = g++
TARGET = mips-sim
D=src/
OBJECTS= $(D)main.cpp $(D)IO.cpp $(D)parser.cpp $(D)disassembler.cpp $(D)memory.cpp $(D)CPU.cpp $(D)pipe.cpp
OBJ=main.o IO.o parser.o disassembler.o memory.o CPU.o pipe.o


all : $(TARGET)

$(TARGET): $(OBJ)
	$(COMP) -o $(TARGET) $(OBJ)

$(OBJ) : $(OBJECTS)
	$(COMP) -c $^

clean:
	rm $(OBJ) $(TARGET)
