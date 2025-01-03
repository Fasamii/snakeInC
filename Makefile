# variables #
BIN_NAME := exe
CC := gcc
FLAGS :=
SRC_DIR:= ./src/
BUILD_DIR := ./build/
# files #
SRC_FILES = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c, $(BUILD_DIR)%.o, $(SRC_FILES))

# make #
$(BIN_NAME) : $(BUILD_DIR) $(OBJ_FILES) 
	$(CC) $(FLAGS) $(OBJ_FILES) -o ./$(BIN_NAME)

$(BUILD_DIR)%.o : $(SRC_DIR)%.c
	gcc -c $< -o $@

$(BUILD_DIR) :
	mkdir -p ./build

# clean #
.PHONY : clean
clean : 
	rm -r $(BUILD_DIR)
	rm ./$(BIN_NAME)
