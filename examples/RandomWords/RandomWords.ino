#include "EnglishList.h"
#include <WordStorage.h>

WordStorage wordStore;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor

  // Start the library with your specific table from WordLists.h
  wordStore.begin(cat_table, NumberOfCategories);

  Serial.println(F("--- Random Word Generator Starting ---"));
  
  if (!wordStore.isInitialized()) {
    Serial.println(F("Error: WordStorage not initialized!"));
  }
}

void loop() {
  // Check if one second has passed
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    // 1. Pick a random category
    int randomCat = random(0, wordStore.numberOfCategories());
    
    // 2. Get the Category Name (always at index 0)
    wordStore.wordFromCatEntry(randomCat, 0);
    String categoryName = wordStore.word();

    // 3. Get a random word from this category (starting from index 1)
    // totalWords() includes the category name, so we pick from 1 to total-1
    int total = wordStore.totalWords(randomCat);
    int randomWordIdx = random(1, total);
    
    if (wordStore.wordFromCatEntry(randomCat, randomWordIdx)) {
      // 4. Output the result
      Serial.print(F("["));
      Serial.print(categoryName);
      Serial.print(F("] "));
      Serial.println(wordStore.word());
    }
  }
}
