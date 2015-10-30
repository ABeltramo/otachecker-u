CPP_FILES := $(wildcard PlistCpp/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lcurl
CC_FLAGS :=

TARGET := otachecker

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p bin
	g++ main.cpp -o bin/$@ $^ $(LD_FLAGS)

obj/%.o: PlistCpp/%.cpp main.cpp
	@mkdir -p obj
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	@rm -rf obj bin
