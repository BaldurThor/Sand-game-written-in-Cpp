#All the object files that need to be compiled
OBJS := main.cpp RNG/RNG.cpp renderer/gridOperations.cpp renderer/render.cpp renderer/renderer.cpp renderer/run.cpp renderer/update.cpp renderer/menu.cpp materials/materialsStruct.cpp materials/pixle.cpp color/colorMixer.cpp button/button.cpp media/mediaHandler.cpp

SRC_DIR := ./src/
OBJS := $(addprefix $(SRC_DIR), $(OBJS))
 
CC = g++
 
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib

COMPILER_FLAGS = -Wall#-w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2

OBJ_NAME = bin/sand.exe

all:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)