#pragma once
#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
#elif defined(__AVR__)
  #include <avr/pgmspace.h>
#else
  #error "Unsupported architecture!"
#endif

class WordStorage {
  private:
    int _katID = 0;
    int _totalWords = 0;
    int _wordIndex = 0;
    int _numberOfCategories = 0;
    const char* const* _catTablePtr = nullptr; // Pointer to table in sketch
    const char* _chosenList = nullptr;
    char _wordBuffer[40];

    int _countWords(const char* flashStr);
    void _getNthWord(const char* flashStr, int n, char* buffer, size_t bufferSize);
    int _calculateIndex(int data);
    void _getListData(int katID);

  public:
    WordStorage();
    void begin(const char* const* table, int count);
    
    int numberOfCategories() const { return _numberOfCategories; }
    int katID() const              { return _katID; }
    int totalWords() const         { return _totalWords; }
    int wordIndex() const          { return _wordIndex; }
    const char* word() const       { return _wordBuffer; }

    int totalWords(int katID);
    bool wordFromData(int data);
    bool wordFromCatEntry(int katID, int entry);
    
    // Safety check: returns true if begin() was called
    bool isInitialized() const { return _catTablePtr != nullptr; }
};
