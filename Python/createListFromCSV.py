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
        with open(INPUT_CSV, 'r', encoding='utf-8') as f:
            # Read all rows into a list
            reader = list(csv.reader(f))
            if not reader:
                return

            # Transpose: Convert columns to rows
            # zip(*reader) takes each row and regroups elements by column index
            columns = list(zip(*reader))

        with open(OUTPUT_HEADER, 'w', encoding='utf-8') as h:
            h.write("#pragma once\n#include <Arduino.h>\n\n")
            h.write("// Auto-generated WordList (Transposed Source)\n")
            h.write("// Format: COLUMN_HEADER/Word1/Word2/...\n\n")
            
            for i, col in enumerate(columns):
                # First element in column is the category header
                category = str(col[0]).strip().upper()
                # Following elements are the words (filtering out empty strings)
                words = [str(w).strip() for w in col[1:] if w.strip()]
                combined = f"{category}/{'/'.join(words)}"
                
                h.write(f'const char p{i}[] PROGMEM = "{combined}";\n')

            h.write("\n// Pointer table to strings in Flash\n")
            pointers = ", ".join([f"p{i}" for i in range(len(columns))])
            h.write(f"const char* const cat_table[] PROGMEM = {{{pointers}}};\n")
            h.write("\nconstexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);\n")

        print(f"Success: {OUTPUT_HEADER} created with {len(columns)} categories.")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    generate_header()
