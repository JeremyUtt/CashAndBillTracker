SRC_DIR 	:= ./src
BUILD_DIR 	:= ./build
BIN_DIR		:= ./bin
INCLUDE_DIR := ./include

TARGET := CBT
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
CFLAGS :=  -I $(INCLUDE_DIR) -c -g -Wall -Wextra -Werror


CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	g++ -o $(BIN_DIR)/$(TARGET) $^ $(LIBS)

# Compile All CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -o $@ $< 

debug:
	@echo $(OBJS)
clean:
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

run: all
	@./$(BIN_DIR)/$(TARGET)

# Dependencies:
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h $(INCLUDE_DIR)/layout.h $(INCLUDE_DIR)/main.h
$(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
$(BUILD_DIR)/Item.o: $(SRC_DIR)/Item.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
$(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h