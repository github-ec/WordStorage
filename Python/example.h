#pragma once
#include <Arduino.h>

// Auto-generated WordList (Transposed Source)
// Format: COLUMN_HEADER/Word1/Word2/...

const char p0[] PROGMEM = "EMOTIONS/Happy/Sad/Angry/Scared";
const char p1[] PROGMEM = "COLORS/Red/Green/Blue/White";
const char p2[] PROGMEM = "ROOMS/Kitchen/Cellar/Attic";

// Pointer table to strings in Flash
const char* const cat_table[] PROGMEM = {p0, p1, p2};

constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);
