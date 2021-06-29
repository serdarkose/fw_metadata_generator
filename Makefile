TARGET = generate_metadata
CC = gcc

HEADERS := $(wildcard *.h)
CPPFLAGS := -I. -MMD -MP
CFLAGS = -I.  -Wall -O2
LDLIBS := -lm

BUILD_DIR := build
SRC_DIR := src
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := .

EXE := $(BIN_DIR)/$(TARGET)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean debug add_debug_flag

all: $(EXE)


$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#.PRECIOUS: $(TARGET) $(OBJ)


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@


clean:
	@$(RM) -rv $(BUILD_DIR) $(OBJ_DIR)
	@$(RM)  $(EXE)

debug: | add_debug_flag all


add_debug_flag:
	$(eval CFLAGS += -g)
	echo $(CFLAGS)