"# MiniFs" 
# MiniFS – A Mini File System with Caching and Lazy Writes

## Project Overview
MiniFS is a user-level simulation of a simple file system designed to demonstrate core operating system concepts such as disk block management, file metadata, caching, and lazy write strategies. It provides basic file operations like `init`, `write`, `read`, and `flush` through a modular C implementation that mimics real file systems.

## Objectives
- Simulate a disk using a binary file.
- Divide the disk into fixed-size blocks.
- Implement a file system with metadata (similar to inodes).
- Manage an in-memory cache with lazy write-back.
- Provide a command-line interface for basic file operations.

## Key Features

| Feature           | Description                                                |
|-------------------|------------------------------------------------------------|
| Disk Simulation   | 1MB file (`disk.img`) acts as a virtual disk divided into 1KB blocks. |
| Metadata Management | File metadata includes name, size, and pointers to disk blocks. |
| In-Memory Cache  | Modified blocks cached in memory and written back on flush or shutdown. |
| Lazy Write       | Delays disk writes to improve performance.                  |
| CLI Interface    | Simple CLI supporting commands like `init`, `write`, `read`, and `flush`. |

## Project Structure

## Supported Commands

| Command                         | Description                                |
|--------------------------------|--------------------------------------------|
| `./minifs init`                 | Initialize the file system and create disk.img. |
| `./minifs write <file> "<text>"` | Write text data to a specified file.     |
| `./minifs read <file>`          | Read and display contents of a specified file. |
| `./minifs flush`                | Flush all modified (dirty) blocks to disk. |
| `./minifs open <file>`          | Not implemented; prints a note.             |
| `./minifs close <file>`         | Not implemented; prints a note.             |
| `./minifs fsck`                 | Stub for file system check; not implemented.|

## Caching and Lazy Write Policy
- Recently modified blocks are cached in memory.
- Blocks are only written to disk when `flush` is called or when the program exits.
- This lazy write-back reduces frequent disk writes and improves performance.

## Limitations
- No open/close state tracking (commands are stubs).
- File system check (`fsck`) is not implemented.
- No support for file deletion or block reuse.
- Only small text files supported due to fixed block allocation.

## Building and Running

Compile the project using:
```bash
gcc -o minifs main.c fs_core.c cache.c disk.c utils.c

./minifs init
./minifs write myfile "Hello, MiniFS!"
./minifs read myfile
./minifs flush

