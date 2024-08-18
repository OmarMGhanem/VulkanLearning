CFLAGS= -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi


BUILD_DIR = build
BIN_DIR = bin
BIN_OUTPUT_DIR = $(BUILD_DIR)/$(BIN_DIR)

enviroment:
	mkdir -p $(BIN_OUTPUT_DIR)

VulkanTest: *.cpp *.hpp enviroment
	g++ $(CFLAGS) -o $(BIN_OUTPUT_DIR)/VulkanTest *.cpp $(LDFLAGS)

CompileShaders:
	./compile.sh


.PHONY: test clean

test: enviroment VulkanTest CompileShaders
	(export DISPLAY=:0; ./build/bin/VulkanTest)
clean:
	rm -rf $(BUILD_DIR)
