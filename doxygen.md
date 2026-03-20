# WordStorage Class Reference

Class for managing slash-separated string lists stored in Flash memory.

`#include <WordStorage.h>`

## Description

This class provides mechanisms to read word lists from PROGMEM (Flash) using a forward slash ('/') as a delimiter. It efficiently parses slash-separated strings to save RAM on AVR and ESP32 platforms.

## Public Functions


| Selection | Name |
| --- | --- |
|  | **[WordStorage](#function-wordstorage)**() <br>Constructor for the WordStorage class. |
| void | **[begin](#function-begin)**(const char *const *table, int count) <br>Initializes the class with a Flash-resident table. |
| int | **[numberOfCategories](#function-numberofcategories)**() const <br>Total number of categories available. |
| int | **[katID](#function-katid)**() const <br>The ID of the currently selected category. |
| int | **[totalWords](#function-totalwords)**() const <br>Number of words available in the current category. |
| int | **[wordIndex](#function-wordindex)**() const <br>The index of the last word loaded into the buffer. |
| const char * | **[word](#function-word)**() const <br>Pointer to the buffer containing the current word. |
| int | **[totalWords](#function-totalwords-1)**(int katID) <br>Counts words in a specific category. |
| bool | **[wordFromData](#function-wordfromdata)**(int data) <br>Loads a word based on a combined data value. |
| bool | **[wordFromCatEntry](#function-wordfromcatentry)**(int katID, int entry) <br>Fetches a specific word from a specific category. |
| bool | **[isInitialized](#function-isinitialized)**() const <br>Safety check to verify initialization. |

---

## Function Documentation

### <a name="function-wordstorage"></a> WordStorage()
Constructor for the WordStorage class.

### <a name="function-begin"></a> void begin(const char *const *table, int count)
Initializes the class with a Flash-resident table.
* **Parameters:**
    * `table`: Pointer to an array of string pointers (in Flash).
    * `count`: Total number of categories within the table.

### <a name="function-totalwords-1"></a> int totalWords(int katID)
Counts words in a specific category.
* **Parameters:**
    * `katID`: The ID of the category to check.
* **Returns:** Number of words found (delimited by '/').

### <a name="function-wordfromdata"></a> bool wordFromData(int data)
Loads a word based on a combined data value.
* **Parameters:**
    * `data`: Integer value encoding both category and word index.
* **Returns:** true if the word was successfully loaded, false otherwise.

### <a name="function-wordfromcatentry"></a> bool wordFromCatEntry(int katID, int entry)
Fetches a specific word from a specific category.
* **Parameters:**
    * `katID`: The ID of the category.
    * `entry`: The zero-based index of the word within that category.
* **Returns:** true if the word exists and was loaded into the buffer.
