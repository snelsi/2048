#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <ctime>

void playgame();                  // Initialize game

void match(int **arr);            // Start new match

void setColor(int color);         // Set Console text color
void setCellColor(int a);         // Cell setColor set (depending on cell value)
void printField(int **arr);       // Print field on the screen
void randfill(int **arr);         // Add new number when move

bool check(int **arr);            // Is there any moves left
void winMenu();                   // User got to 2048

bool movefuncUP(int **arr);       // Shift cells up
bool movefuncDOWN(int **arr);     // Shift cells down
bool movefuncLEFT(int **arr);     // Shift cells left
bool movefuncRIGHT(int **arr);    // Shift cells right

bool exitFunction();              // Question to user: exit or new game
