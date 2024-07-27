CC = gcc
CFLAGS = -std=c11 -Wall -Werror
RELEASE_FLAGS = -O2
RAYLIB = -lraylib
LIBLIST = -lGL -lm -lpthread -ldl -lrt -lX11
LIB = lib/
INCLUDE = include/
SRC = src
BUILD = build

ifeq ($(OS), Windows_NT)
	LIBLIST = -lopengl32 -lgdi32 -lwinmm
endif

SRCS := $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/*/*.c) $(wildcard $(SRC)/*/*/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

EXEC = PWC

.PHONY: all create_build_dir create_web_dist_dir clean
.DEFAULT: all

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(RAYLIB) $(LIBLIST) -L $(LIB) -I $(INCLUDE) -o $(EXEC)

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

create_web_dist_dir:
	mkdir -p web

release: CFLAGS += $(RELEASE_FLAGS)
release: all

web: CC = emcc
web: EXEC = web/PWC.html
web: CFLAGS += -DPLATFORM_WEB
web: RAYLIB = -lraylibweb -s USE_GLFW=3 --shell-file setup/raylib/src/minshell.html --preload-file assets
web: create_web_dist_dir
web: all

clean:
	rm -rf build
	rm -rf web
	rm -f $(EXEC).exe
	rm -f $(EXEC)