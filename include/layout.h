#ifndef LAYOUT_H
#define LAYOUT_H

// ======= Positions =======

#define NAME_START_X 20
#define NAME_START_Y 60


// The buffer inbetween the edge of the window and the title
#define LEFT_OFFSET 20
#define TOP_OFFSET 20

#define TOTAL_START_X 210
// The starting X position for left most buttons
#define BUTTON_START_X TOTAL_START_X + 100

// ======= Spacing =======

// The x distance between each item
// (end-to-start)
#define ITEM_X_SPACING 20
// The Y distance between each item dispayed
// (start-to-start)
#define ITEM_Y_SPACING 50


// ======= Button Size =======

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40

// ======== Colors ========

#define BACKGROUND_COLOR 0x20212400
#define BUTTON_COLOR_OFF 0xa60d2c00
#define BUTTON_COLOR_ON  0x177fbfff


// ======= Text ======

#define FONT_SIZE 20 

// ======= Per User Totals =======

#define USER_TOTAL_X 20

// start to start spacing
#define USER_SPACING_X 100
#define USER_SPACING_Y 30

#endif