SRC_DIR 	:= ./src
BUILD_DIR 	:= ./build
BIN_DIR		:= ./bin
INCLUDE_DIR := ./include

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \

CFLAGS :=  -I $(INCLUDE_DIR) -c -g

all: bin/main

$(BIN_DIR)/main: $(OBJS)
	g++ -o $(BIN_DIR)/main -lsfml-graphics -lsfml-window -lsfml-system ./$^

# Compile All CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -o $@ ./$< 

debug:
	@echo $(OBJS)
clean:
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

run: all
	@./$(BIN_DIR)/main


	 