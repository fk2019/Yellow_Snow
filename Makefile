TARGET = yellow-snow
BUILD_DIR = .build
SOURCE_DIR = src
CC ?= gcc
CFLAGS = -std=c99 $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer)
LDLIBS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer)
SRCS = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))
$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(SOURCE_DIR)/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDLIBS)

.PHONY: all clean run rebuild

all: $(TARGET)

clean:
	$(RM) -r $(TARGET) $(BUILD_DIR)

run: $(TARGET)
	./$<

rebuild: clean all
