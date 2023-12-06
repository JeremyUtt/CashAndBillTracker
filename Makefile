SRC_DIR 	:= ./src
BUILD_DIR 	:= ./build
BIN_DIR		:= ./bin
INCLUDE_DIR := ./include

TARGET := CBT
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
CFLAGS :=  -I $(INCLUDE_DIR) -c -g


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


	 