#pragma once
#include <Arduino.h>

/**
 * @file WordStorage.h
 * @brief Class for managing slash-separated string lists stored in Flash memory.
 * 
 * This class provides mechanisms to read word lists from PROGMEM (Flash) 
 * using a forward slash ('/') as a delimiter.
 */

#if defined(ARDUINO_ARCH_ESP32)
#elif defined(__AVR__)
  #include <avr/pgmspace.h>
#else
  #error "Unsupported architecture!"
#endif

/**
 * @class WordStorage
 * @brief Handles retrieval of words from categorized Flash memory tables.
 * 
 * Efficiently parses slash-separated strings to save RAM on AVR and ESP32 platforms.
 */
class WordStorage {
  private:
    int _katID = 0;              ///< Currently selected category ID
    int _totalWords = 0;         ///< Number of words in the current list
    int _wordIndex = 0;          ///< Index of the currently loaded word
    int _numberOfCategories = 0;  ///< Total count of available categories
    const char* const* _catTablePtr = nullptr; ///< Pointer to the master table in Flash
    const char* _chosenList = nullptr;         ///< Pointer to the active category string
    char _wordBuffer[40];        ///< Internal buffer for the extracted word

    int _countWords(const char* flashStr);
    void _getNthWord(const char* flashStr, int n, char* buffer, size_t bufferSize);
    int _calculateIndex(int data);
    void _getListData(int katID);

  public:
    /**
     * @brief Constructor for the WordStorage class.
     */
    WordStorage();

    /**
     * @brief Initializes the class with a Flash-resident table.
     * @param table Pointer to an array of string pointers (in Flash).
     * @param count Total number of categories within the table.
     */
    void begin(const char* const* table, int count);
    
    /** @return Total number of categories available. */
    int numberOfCategories() const { return _numberOfCategories; }
    
    /** @return The ID of the currently selected category. */
    int katID() const              { return _katID; }
    
    /** @return Number of words available in the current category. */
    int totalWords() const         { return _totalWords; }
    
    /** @return The index of the last word loaded into the buffer. */
    int wordIndex() const          { return _wordIndex; }
    
    /** @return Pointer to the buffer containing the current word. */
    const char* word() const       { return _wordBuffer; }

    /**
     * @brief Counts words in a specific category.
     * @param katID The ID of the category to check.
     * @return Number of words found (delimited by '/').
     */
    int totalWords(int katID);

    /**
     * @brief Loads a word based on a combined data value.
     * @param data Integer value encoding both category and word index.
     * @return true if the word was successfully loaded, false otherwise.
     */
    bool wordFromData(int data);

    /**
     * @brief Fetches a specific word from a specific category.
     * @param katID The ID of the category.
     * @param entry The zero-based index of the word within that category.
     * @return true if the word exists and was loaded into the buffer.
     */
    bool wordFromCatEntry(int katID, int entry);
    
    /**
     * @brief Safety check to verify initialization.
     * @return true if begin() has been called with a valid table.
     */
    bool isInitialized() const { return _catTablePtr != nullptr; }
};
