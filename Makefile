CC = gcc
CFLAGS = -Wall -Werror -g -std=c99

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/player.c \
            $(SRC_DIR)/map.c \
            $(SRC_DIR)/window.c \
            $(SRC_DIR)/renderer.c \
            $(SRC_DIR)/raycaster.c \
						$(SRC_DIR)/utils.c \
						$(SRC_DIR)/inputs.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OUTPUT = raycast

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(OUTPUT) -lSDL2 -lSDL2_ttf -lm

clean:
	rm -f $(OBJ_DIR)/*.o $(OUTPUT)

rebuild: clean $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: clean rebuild run

