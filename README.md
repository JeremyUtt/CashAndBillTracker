# Dependencies
- OpenGL
- GLFW
- imGUI

# Installation
## Build from Source
Install dependencies:
```yay -S extra/glfw```

- Install Imgui source to a location of choice

```git clone https://github.com/ocornut/imgui.git```

- Clone this Repo
```git clone https://github.com/JeremyUttCashAndBillTracker```

- open the Makefile and set the `IMGUI_DIR` variable to the location of the imgui repo 

- run `make`

- optionally: run `make install` to install binary, icon, and .desktop file to youe system (requires sudo)

# Usage
you can either pass in a csv file as a command line argument, or just open the app on its own. you can add items and users to the list through the provided imgui windows
