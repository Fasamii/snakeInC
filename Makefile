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
	@echo -e " linking obiects into \e[38;5;5m$(BIN_NAME)\e[0m file"
	@$(CC) $(FLAGS) $(OBJ_FILES) -o ./$(BIN_NAME)
	@echo -e "\e[38;5;2m dingg done\e[0m"

$(BUILD_DIR)%.o : $(SRC_DIR)%.c
	@echo -e "󰐱 making \e[38;5;5m$@\e[0m from \e[38;5;5m$?\e[0m file"
	@gcc -c $? -o $@

$(BUILD_DIR) :
	@echo -e "\e[38;5;3m no build folder\e[0m"
	@mkdir -p ./build
	@echo -e "\e[38;5;2m build folder created\e[0m"


# clean #
.PHONY : clean
clean : 
	@rm -rf $(BUILD_DIR)
	@echo -e "󰮞 removed \e[38;5;5mbuild\e[0m dir file"
	@rm -f ./$(BIN_NAME)
	@echo -e "󱪠 removed \e[38;5;5mexe\e[0m file"
	@echo -e "\e[38;5;2m dingg done\e[0m"
