SOURCE_DIR=engine/src
OBJECT_DIR=engine/bin
SOURCES=$(shell find $(SOURCE_DIR)/*.c)
TMP_OBJS=$(patsubst %.c, %.o, $(SOURCES))
OBJS=$(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(TMP_OBJS))

TARGET=engine.so
FLAGS= -I engine/include/
all: $(OBJECT_DIR) $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	gcc -shared -o $@ $^

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	gcc -fPIC $^ -o $@ -shared

$(OBJECT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJECT_DIR)
	rm -rf $(TARGET)