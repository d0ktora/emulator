CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c99 -g

SRC_DIR = src
BUILD_DIR = build
RELEASE_DIR = release

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEPS = $(wildcard $(SRC_DIR)/*.h)

TARGET = $(RELEASE_DIR)/emulator

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(RELEASE_DIR)

run: $(TARGET)
	./$(TARGET)


.PHONY: all clean
