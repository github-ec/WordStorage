# WordStorage Example: Random Word Generator

This sketch demonstrates how to use the `WordStorage` library to retrieve and display categorized strings stored in the microcontroller's **Flash memory (PROGMEM)**. It is designed to minimize RAM usage by processing slash-separated lists directly from Flash.

## Features
- **Flash-Based Storage:** Efficiently accesses large word lists (from `EnglishList.h`) without consuming RAM.
- **Dynamic Category Handling:** Automatically detects the number of words in a category and handles the first entry as a header.
- **Non-Blocking Logic:** Uses a `millis()` timer to generate a new word every second.

## Functional Logic

### 1. Data Structure
The sketch expects the word lists to be formatted with a **forward slash (`/`)** as a delimiter. 
- **Index 0:** Category Name (e.g., "ANIMALS").
- **Index 1 to N:** Words belonging to that category (e.g., "Dog", "Cat").

### 2. Initialization
In `setup()`, the `wordStore.begin()` function links the library to the `cat_table` and the total number of categories defined in your header file.

### 3. Execution (The Loop)
Every 1000ms, the following steps are performed:
1. **Random Category:** A category is picked using `random()`.
2. **Category Name:** The string at index `0` is retrieved as the label.
3. **Random Word:** A random index between `1` and the total number of words is chosen to fetch the actual entry.
4. **Serial Output:** The result is formatted as `[Category] Word`.

## Implementation (Sketch)

```cpp
#include "EnglishList.h"
#include <WordStorage.h>

WordStorage wordStore;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial); 

  // Initialize with table and category count from EnglishList.h
  wordStore.begin(cat_table, NumberOfCategories);

  Serial.println(F("--- Random Word Generator Starting ---"));
  
  if (!wordStore.isInitialized()) {
    Serial.println(F("Error: WordStorage not initialized!"));
  }
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    // 1. Pick a random category index
    int randomCat = random(0, wordStore.numberOfCategories());
    
    // 2. Extract Category Name (Index 0)
    wordStore.wordFromCatEntry(randomCat, 0);
    String categoryName = wordStore.word();

    // 3. Extract a random word (Index 1 to Total-1)
    int total = wordStore.totalWords(randomCat);
    int randomWordIdx = random(1, total);
    
    if (wordStore.wordFromCatEntry(randomCat, randomWordIdx)) {
      Serial.print(F("["));
      Serial.print(categoryName);
      Serial.print(F("] "));
      Serial.println(wordStore.word());
    }
  }
}
