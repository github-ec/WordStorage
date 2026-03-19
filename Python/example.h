#pragma once
#include <Arduino.h>

// Generated: 2026/03/19 19:25:16
// ------------------------------------------
// ID  | Category Name    | Words
// ----|------------------|----------
//  0  | EMOTIONS         |      4
//  1  | COLORS           |      4
//  2  | ROOMS            |      3
// ------------------------------------------

const char p0[] PROGMEM = "EMOTIONS/Happy/Sad/Angry/Scared";
const char p1[] PROGMEM = "COLORS/Red/Green/Blue/White";
const char p2[] PROGMEM = "ROOMS/Kitchen/Cellar/Attic";

// Pointer table to strings in Flash
const char* const cat_table[] PROGMEM = {p0, p1, p2};

constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);

