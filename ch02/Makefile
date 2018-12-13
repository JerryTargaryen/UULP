#Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
OTHERS = $(shell find . -name "*~")
EXE_FILES = $(patsubst %.c, %, $(C_SOURCES))

CC = gcc


all: $(C_OBJECTS) $(EXE_FILES) 

.PHONY :clean
clean:
	rm $(C_OBJECTS) $(OTHERS) $(EXE_FILES)


