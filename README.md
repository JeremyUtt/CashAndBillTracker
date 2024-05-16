Colorado School of Mines CSCI 200 Final Project 

## PROBLEM DESCRIPTION:
I am developing a bill splitter app that simplifies the process of dividing expenses among
a group of users. The program will store a list (in the form of a vector) of purchased items and
their prices, allowing each participant to specify whether they are 'in' on any individual item or
not. The item information is inputted either through the terminal, or through a csv file input.
The all will then open a SFML window where users can make their selections.
as users update preferences, the app calculates the amount each individual
owes to the person who made the purchases. If multiple users contribute to a single item, the
app evenly distributes the cost among them. This project aims to solve the real world problem
of me and my roommates splitting the bills after buying groceries. 

## PROGRAM DOCUMENTATION:
This program will need to be built with sfml. The makefile provided is based off the one used in class
so it should link fine as long as sfml is installed. to use the program, run "make run" or 
or run ./billTracker directly. There are example CSV input files in the ./examples directory.
To use the program once the GUI opens, you can click on the user boxes to select them. This will
this will cause the user selected to "add to cart" the item in the selected column. 

In terms of modifying and extending the program, I abstracted a lot of the UI positions and scaling
into its own file "./include/layout.h". this makes it easier to change colors, 
move elements around, change font size, etc. 

Some features that I would have liked to add are:
* enter a filename as a command line argument
    * this sounds relatively simple, just check for an cmd argument and 
       immediately call getCSV(string fileName) is found.
* make the UI look nicer
    * I was mainly time and creativity restrained on this one
* allow items to be added/edited/removed from within the GUI
    * this may require implementing a text input box class to SFML


Some things that changed after the proposal were the structure of the classes.
instead of users storing what item they have, items now store which users have bought them.
this makes a lot of internal logic easier to code. In addition, I added a Button class
to allow input in SFML. most of the Class complexity went into this class as the other 2 
turned out to be less complex than expected

