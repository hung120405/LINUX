CUR_DIR = .
BIN_DIR = $(CUR_DIR)/bin
OBJ_DIR = $(CUR_DIR)/obj
INC_DIR = $(CUR_DIR)/inc
SRC_DIR = $(CUR_DIR)/src
LIB_DIR = $(CUR_DIR)/lib

LIB_SHARED_DIR = $(LIB_DIR)/shared
BIN_NAME := use-shared-library
LIB_NAME := person

HEADER_FLAGS := -I $(INC_DIR)

create_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(HEADER_FLAGS)
	gcc -c -fPIC $(SRC_DIR)/$(LIB_NAME).c -o $(OBJ_DIR)/$(LIB_NAME).o $(HEADER_FLAGS)

create_lib:
	gcc -shared $(OBJ_DIR)/$(LIB_NAME).o -o $(LIB_SHARED_DIR)/lib$(LIB_NAME).so

linking:
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/$(BIN_NAME)

all: create_obj create_lib linking

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(BIN_DIR)/$(BIN_NAME)