CPP_FILES := $(wildcard PlistCpp/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -lcurl
CC_FLAGS :=

otachecker: $(OBJ_FILES)
	g++ $(LD_FLAGS) main.cpp -o $@ $^

obj/%.o: PlistCpp/%.cpp main.cpp
	g++ $(CC_FLAGS) -c -o $@ $<


