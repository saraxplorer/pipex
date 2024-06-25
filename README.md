# Concepts used in the project
1. fork
    ```c
   #include <unistd.h>
   pid_t fork(void);
   ```
    pid_t represents a process ID, which is an integer type. fork creates a new process (child process) that is a duplicate of the
   calling process (parent process). If fork is called once, there will be two processes (parent and child). If fork is called
   twice, each process (both the parent and child from the first fork) will create a new child, resulting in a total of four
   processes.The fork function returns a value of 0 to the child process. It returns the child process ID (PID) to the parent
   process.

3. access
   ``` c
   #include <unistd.h>
   int access(const char *pathname, int mode)
   ```
   The access function is used to check a user's permissions for a file. It checks whether the calling process can access the file
   specified by a pathname for the given mode (such as read, write, or execute permissions). \
   pathname: A pointer to the null-terminated string that specifies the path of the file whose accessibility is to be checked.\
   mode: An integer that specifies the accessibility check(s) to be performed. It can be a bitwise OR of one or more of the
   following     constants:\
   R_OK: Check for read permission. \
   W_OK: Check for write permission. \
   X_OK: Check for execute permission. \
   F_OK: Check for existence of the file.

   Return Value
   Returns 0 if the requested access is permitted.
   Returns -1 if the requested access is not permitted, and errno is set to indicate the error.

3. perror
   ``` c
   #include <stdio.h>
   void perror(const char *s)
   ```
   perror is a function in C that helps to print custom error messages in standard error. It internally uses errno and strerror to
   print error messages. so it is a good practice to add their repective libraries as well but not necessary when using only perror.
   
4. open(argv[i], O_CREAT | O_WRONLY | O_TRUNC, 0644)\
   this code opens a file for writing, creates it if it doesn't exist, and clears its contents if it already exists(O_TRUNC). The new
   file (if created) will have permissions that allow the owner to read and write, while others can only read.\
   6 (owner) : read(4) + write (2) = 6
   4 (group) : read (4)
   4 (others): read (4)
5. KEY-VALUE Pair\
   A key-value pair is a fundamental data structure used to store data. Each key-value pair consists of two parts:\
   Key: A unique identifier for a piece of data. (NAME)\
   Value: The data associated with the key.
   Example
   in the context of environment variables:
   Key: PATH\
   Value: /usr/local/bin:/usr/bin:/bin\
   This means that the PATH environment variable has a value of /usr/local/bin:/usr/bin:/bin, which is a list of directories where
   executable programs are located.
6. Environment Variables
   They are key-value variables stored in the operating system. Example: envp

