# get_next_line

## 📖 Overview
The goal of this project is to implement a function that reads a line from a file descriptor, returning one line at a time.

Prototype:
```c
char    *get_next_line(int fd);
```

- Returns a line ending with `\n` (if present).  
- Returns the last line if the file does not end with `\n`.  
- Returns `NULL` when there is nothing else to read or on error.  

The bonus part requires handling multiple file descriptors at once.

---

## 📂 Files
- `get_next_line.c` → main function logic  
- `get_next_line_utils.c` → helper functions  
- `get_next_line.h` → header file  
- `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` → bonus multi-fd version  

---

## ⚙️ Compilation
Compile with:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> \
   get_next_line.c get_next_line_utils.c main.c
```

Example:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c main.c
```

---

## 📝 Usage
Run with a file:
```bash
./a.out sample.txt
```

Run with standard input (fd = 0):
```bash
./a.out
```
Type text and press **Enter**.  
Press **Ctrl+D** to end input.

---

## ✅ Tests
1. Empty file → returns `NULL`.  
2. File with one line ending in `\n`.  
3. File with one line without `\n`.  
4. Multiple lines with different lengths.  
5. `BUFFER_SIZE = 1` and large values.  
6. Bonus: two files read alternately with different fds.  

---

## 🚀 Skills
- File descriptors (`read`)  
- Dynamic memory management (`malloc`, `free`)  
- Static variables for persistent state  
- Edge cases (EOF, empty file, last line)  
- Modular helper functions  
