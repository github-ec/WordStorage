The WordStorage Class makes it easy to handle arrays with words stored in the flash memory of an ESP32 or an AVR controller such as an Arduino UNO or NANO.

The words can be listed in a separate file or included in the main sketch with the following structure
```cpp
#pragma once
#include <Arduino.h>

/* 
 * STRUCTURE DEFINITION:
 * Each string (p0, p1, etc.) represents a category.
 * - The FIRST word is the Category Name.
 * - All following words are the specific entries.
 * - Words must be separated by a forward slash '/'.
 * - No spaces should surround the slash unless intended as part of the word.
 * - PROGMEM ensures the data stays in Flash memory (crucial for AVR/Arduino Nano).
 */

// Example: Category "EMOTIONS" with 4 words
const char p0[] PROGMEM = "EMOTIONS/Happy/Sad/Angry/Scared";

// Example: Category "COLORS" with 4 words
const char p1[] PROGMEM = "COLORS/Red/Green/Blue/White";

// Example: Category "ROOMS" with 3 words
const char p2[] PROGMEM = "ROOMS/Kitchen/Cellar/Attic";

// Pointer table: Stores the addresses of the strings in Flash memory
const char* const cat_table[] PROGMEM = {p0, p1, p2};

// Compile-time calculation of the number of categories
constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);
```

Key Rules for the Structure:
* **Index 0 is the Name:** The WordStorage library is designed to treat the very first element of each string as the header/category name.
* **Delimiters:** Only use the / character to separate words. Do not end the string with a slash.
* **Flash Memory:** Always use const char[] PROGMEM for the strings and const char* const[] PROGMEM for the table to prevent the RAM from filling up.

The structure of the list and the functions of the WordStorage Class support AVR as well as ESP32 architecture.

There is a Python script that automatically creates an appropriate header file from a CSV file. See under "Python"
