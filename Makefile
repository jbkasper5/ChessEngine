ENGINE_DIR=engine

SOURCE_DIR=$(ENGINE_DIR)/src
OBJECT_DIR=$(ENGINE_DIR)/bin
SOURCES=$(shell find $(SOURCE_DIR)/*.c)
TMP_OBJS=$(patsubst %.c, %.o, $(SOURCES))
OBJS=$(patsubst $(SOURCE_DIR)/%, $(OBJECT_DIR)/%, $(TMP_OBJS))

TARGET=libs/lib.so
FLAGS= -I $(ENGINE_DIR)/include/
all: $(OBJECT_DIR) $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	gcc -arch x86_64 -fPIC -shared -o $@ $^

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	gcc -arch x86_64 -fPIC $^ -o $@ -shared

$(OBJECT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJECT_DIR)
	rm -rf $(TARGET)