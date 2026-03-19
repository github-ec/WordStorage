# WordStorage Class Documentation
The `WordStorage` class is designed to manage and retrieve strings (words) stored in the **Flash memory (PROGMEM)** of an Arduino or ESP32. It allows for efficient memory usage by keeping large text lists out of the RAM.
## Features- 
**Architecture Support:** Compatible with 
**AVR** (e.g., Uno, Mega) and **ESP32**.- 

**RAM Efficiency:** Strings are processed directly from Flash memory.-

**Dynamic Parsing:** Automatically counts and extracts 
**slash-separated (/)** words.-

**Data Mapping:** Supports mapping a single integer ID to specific category/word pairs.

## Setup & Initialization
To use this class, define your strings and a pointer table using the `PROGMEM` keyword. **Important:** Use a forward slash `/` as the delimiter between words.

```cpp
#include "WordStorage.h"

// Strings stored in Flash (Words separated by '/')
const char cat_0[] PROGMEM = "Apple/Banana/Cherry/Date";
const char cat_1[] PROGMEM = "Dog/Cat/Elephant";

// Table of pointers to the strings
const char* const masterTable[] PROGMEM = { cat_0, cat_1 };

WordStorage storage;

void setup() {
    // Initialize with the table and the number of categories (2)
    storage.begin(masterTable, 2);
}

Public API ReferenceConfiguration & Data Retrieval

* void begin(const char* const* table, int count)
Initializes the class with the pointer table and the total number of categories.

* bool wordFromCatEntry(int katID, int entry)
Fetches the n-th word (entry) from category katID. Returns true if successful.

* bool wordFromData(int data)
Calculates a category and word index from a single integer (e.g., for encoded IDs) and loads the corresponding word.

* int totalWords(int katID)
Returns the number of words found in the specified category (based on / separators).

State Getters

* const char* word()
Returns a pointer to the current word stored in the internal _wordBuffer.

* int katID() / int wordIndex()
Returns the currently active category ID or word index.

* int totalWords()
Returns the total word count of the currently selected category.

* bool isInitialized()
Returns true if begin() has been successfully called.

Technical Details

* Delimiter: The class is hardcoded to split strings by the forward slash (/).
* Buffer Size: The internal _wordBuffer is set to 40 characters.
* Architecture Handling: On AVR, the class uses pgm_read_ptr and pgm_read_byte; on ESP32, it uses standard memory access.

------------------------------
Note: Ensure your Flash strings do not contain extra spaces around the slashes unless they are intended to be part of the word.
