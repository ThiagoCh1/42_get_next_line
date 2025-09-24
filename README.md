# 42_get_next_line

## 📖 Overview
The goal of this project is to implement a function that reads a line from a file descriptor, returning one line at a time.

Prototype:
```c
char    *get_next_line(int fd);
Returns a line ending with \n (if present).

Returns the last line if the file does not end with \n.

Returns NULL when there is nothing else to read or on error.

The bonus part requires handling multiple file descriptors at once.

📂 Files
get_next_line.c → main function logic

get_next_line_utils.c → helper functions

get_next_line.h → header file

get_next_line_bonus.c / get_next_line_utils_bonus.c / get_next_line_bonus.h → bonus multi-fd version

main.c → test program (not part of submission)

⚙️ Compilation
bash
Copy code
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> get_next_line.c get_next_line_utils.c main.c
Example:

bash
Copy code
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
📝 Usage
Run with a file:

bash
Copy code
./a.out sample.txt
Run with standard input (fd = 0):

bash
Copy code
./a.out
Type text and press Enter, then press Ctrl+D to end input.

✅ Tests
Empty file → returns NULL.

File with one line ending in \n.

File with one line without \n.

Multiple lines with different lengths.

BUFFER_SIZE = 1 and large values.

Bonus: two files read alternately.

🚀 Skills
File descriptors (read)

Dynamic memory management (malloc, free)

Static variables for persistent state

Edge cases (EOF, empty file, last line)

Modular helper functions
