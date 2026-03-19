import csv
import os
from datetime import datetime

# Configuration
INPUT_CSV = 'example.csv'
OUTPUT_HEADER = 'WordLists.h'

def generate_header():
    if not os.path.exists(INPUT_CSV):
        print(f"Error: {INPUT_CSV} not found!")
        return

    try:
        with open(INPUT_CSV, 'r', encoding='utf-8') as f:
            # Read all rows and transpose them (columns to rows)
            reader = list(csv.reader(f))
            if not reader: return
            columns = list(zip(*reader))

        with open(OUTPUT_HEADER, 'w', encoding='utf-8') as h:
            # 1. Write Header Info
            timestamp = datetime.now().strftime("%Y/%m/%d %H:%M:%S")
            h.write("#pragma once\n#include <Arduino.h>\n\n")
            h.write(f"// Generated: {timestamp}\n")
            h.write("// ------------------------------------------\n")
            h.write("// ID  | Category Name    | Words\n")
            h.write("// ----|------------------|----------\n")
            
            # Temporary storage for string definitions to write them after the comment
            string_definitions = []
            
            # 2. Process columns and prepare table comment
            for i, col in enumerate(columns):
                category = str(col[0]).strip().upper()
                words = [str(w).strip() for w in col[1:] if w.strip()]
                word_count = len(words)
                
                # Add row to the comment table
                h.write(f"//  {i:<2} | {category:<16} | {word_count:>6}\n")
                
                # Prepare the PROGMEM string
                combined = f"{category}/{'/'.join(words)}"
                string_definitions.append(f'const char p{i}[] PROGMEM = "{combined}";')

            h.write("// ------------------------------------------\n\n")
            
            # 3. Write the PROGMEM strings
            for s in string_definitions:
                h.write(f"{s}\n")

            # 4. Write the pointer table
            h.write("\n// Pointer table to strings in Flash\n")
            pointers = ", ".join([f"p{i}" for i in range(len(columns))])
            h.write(f"const char* const cat_table[] PROGMEM = {{{pointers}}};\n")
            h.write("\nconstexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);\n")

        print(f"Success: {OUTPUT_HEADER} created with {len(columns)} categories.")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    generate_header()

