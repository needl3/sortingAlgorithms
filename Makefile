SOURCE_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
COMPILER = g++

SRC_FILES = $(SOURCE_DIR)/*.cpp

FINALEXE = ttt

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

build:
	@$(COMPILER) $(SRC_FILES) -o $(BIN_DIR)/$(FINALEXE) $(FLAGS)

run:
	@./$(BIN_DIR)/$(FINALEXE) 