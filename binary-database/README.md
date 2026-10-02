# Binary Database in C

A small file-based database written in C to practice binary file I/O, structs, file positioning, and record management.

## Features

- Store records in a binary file.
- Maintain a database header containing the record count.
- Read records by index.
- Add, update, find, list, and delete records.
- Open and close the database through a dedicated API.
- Test record persistence by closing and reopening the database.

Each record contains an ID, name, age, and score.

## File Format

The database file consists of a header followed by a sequence of records:

```text
[DatabaseHeader][Record 0][Record 1][Record 2]...
```

The header stores the number of records. Records are accessed using their index and their offset within the file.

**Note:** Records are stored as raw C structs, so the file format is not guaranteed to be portable across different compilers or platforms.

## Build

Compile with GCC:

```bash
gcc main.c database.c -o build/binary_database.exe -Wall -Wextra -Wpedantic
```

Run:

```bash
./build/binary_database.exe
```

The test program checks database creation, file handling, record operations, invalid indexes, and persistence.

## Learning Goals

- Practice `fopen`, `fread`, `fwrite`, `fseek`, and `fclose`.
- Understand binary file layouts and offsets.
- Manage persistent metadata.
- Organize database operations into reusable functions.
- Handle file errors and validate inputs.

## Future Improvements

- Improve portability through explicit field serialization.
- Handle corrupted or truncated database files.
- Improve error handling and recovery after failed writes.

