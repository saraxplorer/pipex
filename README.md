# Concepts
1. fork
 ```c
   #include <unistd.h>
   pid_t fork(void);
   ```
pid_t represents a process ID, which is an integer type. fork creates a new process (child process) that is a duplicate of the calling process (parent process). If fork is called once, there will be two processes (parent and child). If fork is called twice, each process (both the parent and child from the first fork) will create a new child, resulting in a total of four processes.The fork function returns a value of 0 to the child process. It returns the child process ID (PID) to the parent process.

2. access 
``` c
#include <unistd.h>
int access(const char *pathname, int mode)
```
The access function is used to check a user's permissions for a file. It checks whether the calling process can access the file specified by a pathname for the given mode (such as read, write, or execute permissions). \
pathname: A pointer to the null-terminated string that specifies the path of the file whose accessibility is to be checked.\
mode: An integer that specifies the accessibility check(s) to be performed. It can be a bitwise OR of one or more of the following     constants:\
  R_OK: Check for read permission. \
  W_OK: Check for write permission. \
  X_OK: Check for execute permission. \
  F_OK: Check for existence of the file.

Return Value

  Returns 0 if the requested access is permitted.
  Returns -1 if the requested access is not permitted, and errno is set to indicate the error.
