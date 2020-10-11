# Makefile

COMP = g++
TARGET = mips_sim
D=src/
OBJECTS= $(D)main.cpp $(D)IO.cpp $(D)parser.cpp $(D)disassembler.cpp $(D)memory.cpp
OBJ=main.o IO.o parser.o disassembler.o memory.o 

all : $(TARGET)

$(TARGET): $(OBJ)
	$(COMP) -o $(TARGET) $(OBJ)

$(OBJ) : $(OBJECTS)
	$(COMP) -c $^

clean:
	rm $(OBJ) $(TARGET)
