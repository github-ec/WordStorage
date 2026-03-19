#include "WordStorage.h"

WordStorage::WordStorage() {}

void WordStorage::begin(const char* const* table, int count) {
  _catTablePtr = table;
  _numberOfCategories = count;
}

void WordStorage::_getListData(int katID) {
  // Safety: Check if table is initialized
  if (!_catTablePtr || katID < 0 || katID >= _numberOfCategories) {
    _chosenList = nullptr;
    _totalWords = 0;
    return;
  }
  
  _katID = katID;
  _chosenList = (const char*)pgm_read_ptr(&_catTablePtr[katID]);
  _totalWords = _countWords(_chosenList);
}

bool WordStorage::wordFromCatEntry(int katID, int entry) {
  if (!isInitialized()) return false; // Safety exit

  katID = constrain(katID, 0, _numberOfCategories - 1);
  _getListData(katID);
  
  if (!_chosenList || _totalWords == 0) return false;
  
  if (entry < 0) entry = _calculateIndex(-entry);
  if (entry >= 0 && entry < _totalWords) {
    _wordIndex = entry;
    _getNthWord(_chosenList, _wordIndex, _wordBuffer, sizeof(_wordBuffer));
    return true;
  }
  return false;
}

// --- Internal Helper Methods ---

int WordStorage::_countWords(const char* flashStr) {
  if (!flashStr) return 0;
  int count = 0;
  const char* ptr = flashStr;
  char c = pgm_read_byte(ptr);
  while (c != '\0') {
    if (c == '/') count++;
    ptr++;
    c = pgm_read_byte(ptr);
  }
  return (count > 0 || pgm_read_byte(flashStr) != '\0') ? count + 1 : 0;
}

void WordStorage::_getNthWord(const char* flashStr, int n, char* buffer, size_t bufferSize) {
  if (bufferSize == 0 || !flashStr) return;
  int currentWord = 0;
  const char* ptr = flashStr;
  char c = pgm_read_byte(ptr);
  while (currentWord < n && c != '\0') {
    if (c == '/') currentWord++;
    ptr++;
    c = pgm_read_byte(ptr);
  }
  size_t j = 0;
  c = pgm_read_byte(ptr);
  while (j < (bufferSize - 1) && c != '/' && c != '\0') {
    buffer[j++] = c;
    ptr++;
    c = pgm_read_byte(ptr);
  }
  buffer[j] = '\0';
}

int WordStorage::_calculateIndex(int data) {
  if (_totalWords <= 0) return 0;
  int index = (data ^ (int)(millis() & 0xFF)) % _totalWords;
  return abs(index);
}

int WordStorage::totalWords(int katID) {
  if (!isInitialized()) return 0;
  _getListData(constrain(katID, 0, _numberOfCategories - 1));
  return _totalWords;
}

bool WordStorage::wordFromData(int data) {
  if (!isInitialized()) return false;
  return wordFromCatEntry(abs(data) % _numberOfCategories, -data);
}
