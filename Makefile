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
SHH = @ # @ = silent, empty = verbose

.PHONY: all create_build_dir clean
.DEFAULT: all

all: $(EXEC)

$(EXEC): $(OBJS)
	$(SHH) $(CC) $(OBJS) $(CFLAGS) $(LIBLIST) -L $(LIB) -I $(INCLUDE) -o $(EXEC)

$(BUILD)/%.o: $(SRC)/%.c | create_build_dir
	$(SHH) $(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

create_build_dir:
	$(SHH)$-mkdir $(BUILD)
	$(SHH)$-mkdir $(BUILD)\abilities
	$(SHH)$-mkdir $(BUILD)\entities
	$(SHH)$-mkdir $(BUILD)\map

release: CFLAGS += $(RELEASE_FLAGS)
release: all

clean:
	$(SHH)$-rm -r $(BUILD)
	$(SHH)$-rm -f $(EXEC).exe