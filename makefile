#All the object files that need to be compiled
OBJS := main.cpp RNG.cpp

SRC_DIR := ./src/
OBJS := $(addprefix $(SRC_DIR), $(OBJS))
 
CC = g++
 
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib

COMPILER_FLAGS = -Wall#-w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OBJ_NAME = build/sand.exe

all:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)