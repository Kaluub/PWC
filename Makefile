CC = gcc
CFLAGS = -std=c11 -Wall -Werror
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g
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

.PHONY: native debug all create_build_dir create_web_dist_dir clean
.DEFAULT: native

native: CFLAGS += -DPLATFORM_DESKTOP
native:	all

debug: CFLAGS += -DPLATFORM_DESKTOP $(DEBUG_FLAGS)
debug: all

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
release: native

web: CC = emcc
web: EXEC = web/PWC.html
web: CFLAGS += -DPLATFORM_WEB
web: RAYLIB = -lraylibweb -s USE_GLFW=3 --shell-file shell.html --preload-file assets -s ERROR_ON_UNDEFINED_SYMBOLS=0
web: create_web_dist_dir
web: all

clean:
	rm -rf build
	rm -rf web
	rm -f $(EXEC).exe
	rm -f $(EXEC)