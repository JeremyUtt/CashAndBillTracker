SRC_DIR 	:= ./src
INCLUDE_DIRS := -I./include -I/home/jeremy/GitRepos/imgui/ -I/home/jeremy/GitRepos/imgui/backends
BUILD_DIR 	:= ./build
BIN_DIR		:= .

TARGET := billTracker
LIBS := -Llib -lglfw -lGL -limgui
CFLAGS := $(INCLUDE_DIRS) -c -g -O0

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \

all: $(BIN_DIR)/$(TARGET)

# Link objects together
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	g++ -o $(BIN_DIR)/$(TARGET) $^ $(LIBS)

# Compile All CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -o $@ $< 

clean:
	rm $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

run: all
	@./$(BIN_DIR)/$(TARGET)

# Dependencies:
# $(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h $(INCLUDE_DIR)/layout.h $(INCLUDE_DIR)/main.h
# $(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Item.o: $(SRC_DIR)/Item.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h
