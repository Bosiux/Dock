CC := gcc
CFLAGS := -Wall -Wextra -std=c99


SRC_DIR := src
BUILD_DIR := build
HEADER_DIR := header
CLEAN_FILES := build/*


SRCS := $(wildcard $(SRC_DIR)/*.c)


OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))


TARGET := $(BUILD_DIR)/dock

.PHONY: all clean

ifeq (all, $(filter all, $(MAKECMDGOALS)))
$(info already compiled)
endif

all: $(TARGET)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[42m ✔ Compiling: $< into $@ \033[0m"
	@gcc $(CFLAGS) -c $< -o $@


$(TARGET): $(OBJS)
	@gcc $(CFLAGS) $^ -o $@

clean:
	@rm -r $(CLEAN_FILES)
	@echo "\033[43m ‼ Cleaning:  build/ folder is now empty\033[0m"


