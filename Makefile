SRC_DIR 	:= ./src
INCLUDE_DIR := ./include
BUILD_DIR 	:= ./build
BIN_DIR		:= .

TARGET := billTracker
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS :=  -I $(INCLUDE_DIR) -c -g -Wall -Wextra -Werror -pedantic-errors -std=c++17


CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
	Q = 
else
	DEL = rm -f
	Q = "
endif

all: $(BIN_DIR)/$(TARGET)

# Link objects together
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	g++ -o $(BIN_DIR)/$(TARGET) $^ $(LIBS)

# Compile All CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -o $@ $< 

clean:
	$(DEL) -f $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

run: all
	@./$(BIN_DIR)/$(TARGET)

# Dependencies:
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h $(INCLUDE_DIR)/layout.h $(INCLUDE_DIR)/main.h
$(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
$(BUILD_DIR)/Item.o: $(SRC_DIR)/Item.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
$(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h
