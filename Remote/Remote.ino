/*
 Virtual mouse and keyboard for Arduboy
 by Erwin Ried
 
 Based on KeyboardAndMouseControl Example for Arduino Leonardo, Micro or Due by Tom Igoe
*/

#include "Keyboard.h"
#include "Mouse.h"
#include "Arduboy2.h"
#include "Structs.h"

Arduboy2 arduboy;

long waitForRelease = 0;

double inix = 0, iniy = 0; // Keyboard position
int nx = 0, ny = 0; // Desired keyboard position
const double KEYBOARD_SCROLL = 25; // Scroll speed
const int DEBOUNCE = 200; // in ms

const int MOUSE_DEBOUNCE = 20;
const int MOUSE_SPEED = 1,MOUSE_ACCEL = 1, MOUSE_MAXACCEL = 50;
const int MOUSE_DELAY = 400; // in ms
int mouseHeld = 0;
byte mouseBlock = 64, selectedBlock = 1, previousBlock = mouseBlock;


