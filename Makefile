# Main Configuration

TARGET := billTracker

IMGUI_DIR := /home/jeremy/GitRepos/CODE/imgui
NFD_DIR  := /home/jeremy/GitRepos/CODE/nativefiledialog-extended
SRC_DIR 	:= ./src
INCLUDE_DIRS := -I./include -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(NFD_DIR)/src/include
BUILD_DIR 	:= ./build
BIN_DIR		:= .

IMGUI_LIBS := -lglfw -lGL
NFD_LIBS := -lgtk-3 -lgdk-3 -lglib-2.0 -lgobject-2.0
STATIC_LIBS := lib/libimgui.a lib/libnfd.a

IMGUI_SRC := $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
IMGUI_SRC += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

CFLAGS := $(INCLUDE_DIRS) -c -g -O0

LIBS := $(IMGUI_LIBS) $(NFD_LIBS)
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES)) \


all: $(BIN_DIR)/$(TARGET)
libs: $(STATIC_LIBS)


# Link objects together
$(BIN_DIR)/$(TARGET): $(OBJECTS) $(STATIC_LIBS)
	@echo LD $^ '-->' $@
	@g++ -o $(BIN_DIR)/$(TARGET) $^ $(LIBS)

# Compile All main CPP files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo CC $< '-->' $@
	@g++ $(CFLAGS) -o $@ $< 


# Create libimgui.a
lib/libimgui.a: $(IMGUI_SRC)
	@echo $^ '-->' $@
	@cd build && g++ -c $(IMGUI_SRC) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
	@ar rcs $@ build/imgui*.o

# Create libnfd.a
lib/libnfd.a: 
	@echo $^ '-->' $@
	@cd $(NFD_DIR) &&\
	mkdir -p build &&\
	cd build &&\
	cmake -DCMAKE_BUILD_TYPE=Release -DNFD_BUILD_TESTS=OFF .. &&\
	cmake --build .
	@cp $(NFD_DIR)/build/src/libnfd.a lib/libnfd.a


# OTHER

install: all
	@sudo cp $(BIN_DIR)/$(TARGET) /usr/local/bin
	@sudo cp CBT.desktop /usr/share/applications 
	@sudo cp icon.ico /usr/share/icons/cbt.ico 

clean:
	@rm -rf $(TARGET) $(BUILD_DIR)/*

cleanlib: clean
	@rm -rf lib/*

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

run: all
	@./$(BIN_DIR)/$(TARGET) examples/1.csv


# debug:
# 	@echo $(OBJECTS)
# 	@echo $(IMGUI_SRC)

# dynimgui: lib/libimgui.so 
# lib/libimgui.so: $(SOURCES)
# 	g++ -fPIC -shared $(SOURCES) -o lib/libimgui.so -I$(IMGUI_DIR)

# Dependencies:
# $(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h $(INCLUDE_DIR)/layout.h $(INCLUDE_DIR)/main.h
# $(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Item.o: $(SRC_DIR)/Item.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h
# $(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp $(INCLUDE_DIR)/User.h $(INCLUDE_DIR)/Item.h $(INCLUDE_DIR)/Button.h
