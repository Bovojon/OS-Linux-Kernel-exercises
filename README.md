# Linux Kernel

The code is based on questions from the textbook, **Operating System Concepts, 9th Edition by Abraham Silberschatz**.

## Description of files:
* `linux_kernel_linked_list.c`: creates a linked list containing five struct birthday
elements, traverses the linked list and outputs its contents to the kernel log buffer. It then deletes the elements from the linked list and returns the free memory back to the kernel.
* `process_identifier_manager.c`: creates and initializes a data structure for representing process identifiers, allocates and returns a process identifier and releases a process identifier.
* `collatz_conjecture.c`: uses the `fork()` system call to generate the Collatz conjecture sequence in the child process.



## Unix System Calls
The header file `unistd.h` provides access to the POSIX operating system API:
* Process Control:
`fork()` - used to create a new process
`exit()`
`wait()`
* File Manipulation:
`open()`
`read()`
`write()`
`close()`
* Device Manipulation:
`ioctl()`
`read()`
`write`
* Information Maintenance:
`getpid()`
`alarm()`
`sleep()`
* Communication:
`pipe()`
`shm_open()`
`mmap()`
* Protection:
`chmod()`
`unmask()`
`chown()`
