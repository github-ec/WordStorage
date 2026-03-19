import csv
import os

# Configuration
INPUT_CSV = 'words.csv'
OUTPUT_HEADER = 'WordLists.h'

def generate_header():
    if not os.path.exists(INPUT_CSV):
        print(f"Error: {INPUT_CSV} not found!")
        return

    try:
        # Read CSV with UTF-8 encoding to preserve all characters
        with open(INPUT_CSV, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            # Filter out empty rows
            rows = [row for row in reader if row and any(field.strip() for field in row)]

        with open(OUTPUT_HEADER, 'w', encoding='utf-8') as h:
            h.write("#pragma once\n#include <Arduino.h>\n\n")
            h.write("// Auto-generated WordList for SoundPlayer & WordStorage\n")
            h.write("// Structure: CATEGORY_NAME/Word1/Word2/...\n\n")
            
            # Generate individual PROGMEM strings
            for i, row in enumerate(rows):
                # First column is the category name (forced to upper case)
                category = row[0].strip().upper()
                # Following columns are the words
                words = [w.strip() for w in row[1:] if w.strip()]
                combined = f"{category}/{'/'.join(words)}"
                
                h.write(f'const char p{i}[] PROGMEM = "{combined}";\n')

            # Generate the pointer table
            h.write("\n// Pointer table to strings in Flash memory\n")
            pointers = ", ".join([f"p{i}" for i in range(len(rows))])
            h.write(f"const char* const cat_table[] PROGMEM = {{{pointers}}};\n")
            
            # Category count calculation
            h.write("\n// Number of categories calculated at compile time\n")
            h.write("constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);\n")

        print(f"Success: {OUTPUT_HEADER} created with {len(rows)} categories.")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    generate_header()
