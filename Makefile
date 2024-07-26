CC = gcc
CFLAGS = -std=c11 -Wall -Werror
RELEASE_FLAGS = -O2
LIBLIST = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIB = lib/
INCLUDE = include/
SRC = src
BUILD = build

ifeq ($(OS), Windows_NT)
	LIBLIST = -lraylib -lopengl32 -lgdi32 -lwinmm
endif

SRCS := $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*/*.c) $(wildcard $(SRC)/*/*/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

EXEC = PWC

.PHONY: all create_build_dir clean
.DEFAULT: all

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBLIST) -L $(LIB) -I $(INCLUDE) -o $(EXEC)

$(BUILD)/%.o: $(SRC)/%.c | create_build_dir
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

create_build_dir:
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/abilities
	mkdir -p $(BUILD)/drawing
	mkdir -p $(BUILD)/entities
	mkdir -p $(BUILD)/entities/effects
	mkdir -p $(BUILD)/map
	mkdir -p $(BUILD)/math

release: CFLAGS += $(RELEASE_FLAGS)
release: all

clean:
	rm -rf $(BUILD)
	rm -f $(EXEC).exe
	rm -f $(EXEC)