CC = gcc
CFLAGS = -std=c11 -Wall -Werror
RELEASE_FLAGS = -Wl,--subsystem,windows -O2
LIBLIST = -lraylib -lopengl32 -lgdi32 -lwinmm
LIB = lib/
INCLUDE = include/
SRC = src
BUILD = build

SRCS := $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

EXEC = PWC

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBLIST) -L $(LIB) -I $(INCLUDE) -o $(EXEC)

$(BUILD)/%.o: $(SRC)/%.c | create_build_dir
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

.PHONY: create_build_dir
create_build_dir:
	if not exist $(BUILD) mkdir $(BUILD)
	if not exist $(BUILD)\abilities mkdir $(BUILD)\abilities
	if not exist $(BUILD)\entities mkdir $(BUILD)\entities
	if not exist $(BUILD)\map mkdir $(BUILD)\map

release: CFLAGS += $(RELEASE_FLAGS)
release: all

clean:
	rmdir /q /s $(BUILD)
	del /q $(EXEC).exe