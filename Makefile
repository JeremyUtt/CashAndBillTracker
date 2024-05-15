IMGUI_DIR := /home/jeremy/GitRepos/imgui

SRC_DIR 	:= ./src
INCLUDE_DIRS := -I./include -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
BUILD_DIR 	:= ./build
BIN_DIR		:= .

TARGET := billTracker
LIBS := -Llib -lglfw -lGL -limgui
CFLAGS := $(INCLUDE_DIRS) -c -g -O0

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \

IMGUI_SRC := $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_SRC += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp



all: $(BIN_DIR)/$(TARGET)
imgui: lib/imgui.a


# Link objects together
$(BIN_DIR)/$(TARGET): $(OBJECTS) 
	g++ -o $(BIN_DIR)/$(TARGET) $^ $(LIBS)

# Compile All main CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -o $@ $< 

# Compile All imgui CPP files
# lib/imgui.a: $(IMGUI_SRC)
# g++ $(CFLAGS) -o $@ $< 

clean:
	@rm -rf $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

run: all
	@./$(BIN_DIR)/$(TARGET)


dynlibs: lib/libimgui.so 

lib/libimgui.so: $(SOURCES)
	g++ -fPIC -shared $(SOURCES) -o lib/libimgui.so -I$(IMGUI_DIR)



debug:
	@echo $(OBJECTS)
	@echo $(IMGUI_SRC)

# Dependencies:
# $(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h $(INCLUDE_DIR)/layout.h $(INCLUDE_DIR)/main.h
# $(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Item.o: $(SRC_DIR)/Item.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h
