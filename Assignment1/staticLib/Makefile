CUR_DIR = .
BIN_DIR = $(CUR_DIR)/bin
OBJ_DIR = $(CUR_DIR)/obj
INC_DIR = $(CUR_DIR)/inc
SRC_DIR = $(CUR_DIR)/src
LIB_DIR = $(CUR_DIR)/lib

LIB_STATIC_DIR = $(LIB_DIR)/static
BIN_NAME := statically-linked
LIB_NAME := person

HEADER_FLAGS := -I $(INC_DIR)

create_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(HEADER_FLAGS)
	gcc -c $(SRC_DIR)/$(LIB_NAME).c -o $(OBJ_DIR)/$(LIB_NAME).o $(HEADER_FLAGS)

create_lib:
	ar rcs $(LIB_STATIC_DIR)/lib$(LIB_NAME).a $(OBJ_DIR)/$(LIB_NAME).o

linking:
	gcc $(OBJ_DIR)/main.o $(LIB_STATIC_DIR)/lib$(LIB_NAME).a -o $(BIN_DIR)/$(BIN_NAME)

all: create_obj create_lib linking

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_STATIC_DIR)/*.a
	rm -rf $(BIN_DIR)/$(BIN_NAME)
