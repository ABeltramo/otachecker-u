TARGET := otachecker


OBJ_DIR = obj
BIN_DIR = bin

MAIN_FILE := main.cpp
CPP_FILES := $(wildcard PlistCpp/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lcurl
CC_FLAGS :=


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	g++ $(MAIN_FILE) -o $(BIN_DIR)/$@ $^ $(LD_FLAGS)

$(OBJ_DIR)/%.o: PlistCpp/%.cpp
	@mkdir -p $(OBJ_DIR)
	g++ -c -o $@ $< $(CC_FLAGS)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)