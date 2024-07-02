# Concepts used in the project\
A lot of functions are used in this project. So understanding their behavior seems important

1. fork
    ```c
   #include <unistd.h>
   pid_t fork(void);
   ```
    pid_t represents a process ID. fork creates a new process (child process) that is a duplicate of the
   calling process (parent process). If fork is called once, there will be two processes (parent and child). If fork is called
   twice, each process (both the parent and child from the first fork) will create a new child, resulting in a total of four
   processes.The fork function returns a value of 0 to the child process. It returns the child process ID (PID) to the parent
   process.

2. pid_t\
    pid_t is a data type used in C programming on Unix-like operating systems (like Linux). It stands for "process identifier type" and is used to represent process IDs (PIDs).A process ID is a unique identifier for each running process in an operating system.pid_t is defined in the header file <sys/types.h>. but it can also be used from unistd.h.The unistd.h header file includes the definition of pid_t and provides access to getpid(), which returns the process ID of the calling process.

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

4. perror
   ``` c
   #include <stdio.h>
   void perror(const char *s)
   ```
   perror is a function in C that helps to print custom error messages in standard error. It internally uses errno and strerror to
   print error messages. so it is a good practice to add their repective libraries as well but not necessary when using only perror.
   
5. open(argv[i], O_CREAT | O_WRONLY | O_TRUNC, 0644) (from the project source code)\
   this code opens a file for writing, creates it if it doesn't exist, and clears its contents if it already exists(O_TRUNC). The new
   file (if created) will have permissions that allow the owner to read and write, while others can only read.\
   6 (owner) : read(4) + write (2) = 6
   4 (group) : read (4)
   4 (others): read (4)

6. KEY-VALUE Pair
   A key-value pair is a fundamental data structure used to store data. Each key-value pair consists of two parts:\
   Key: A unique identifier for a piece of data. (NAME)\
   Value: The data associated with the key.
   Example
   in the context of environment variables:
   Key: PATH\
   Value: /usr/local/bin:/usr/bin:/bin\
   This means that the PATH environment variable has a value of /usr/local/bin:/usr/bin:/bin, which is a list of directories where
   executable programs are located.
   
7. Environment Variables\
   They are key-value variables stored in the operating system. Example: envp
   
8. pipe
   ``` c
   #include <unistd.h>
   int pipe(int pipefd[2]);
   ```
   the pipe function is used to create a unidirectional communication channel, which can be used for inter-process communication
   (IPC).A pipe is a mechanism that allows data to flow from one process to another.\
   Parameters\
   pipefd: This is an array of two integers. After a successful call to pipe, pipefd[0] will be the file descriptor for the read end
   of the pipe, and pipefd[1] will be the file descriptor for the write end of the pipe.\
   Return Value\
   On success, pipe returns 0.\
   On failure, pipe returns -1 and sets errno to indicate the error.
   
9. dup2
   ``` c
   #include <unistd.h>
   int dup2(int oldfd, int newfd)
   ```
   The dup2 function duplicates a file descriptor, making two file descriptors refer to the same open file description.\
   Parameters\
   oldfd: The file descriptor to be duplicated.\
   newfd: The file descriptor to be made a duplicate of oldfd.\
   Return Value\
   On success, dup2 returns newfd.\
   On failure, it returns -1 and sets errno to indicate the error.\
   Behavior\
   If oldfd is not a valid file descriptor, dup2 returns -1.\
   If oldfd is a valid file descriptor:\
   If oldfd and newfd are the same, dup2 does nothing and simply returns newfd.\
   If oldfd and newfd are different, dup2 first closes newfd if it is open, then makes newfd a duplicate of oldfd. After duplication,
   oldfd and newfd refer to the same open file description, meaning they share the same file offset, file status flags, etc.The
   reason newfd is closed before being duplicated is to ensure that it does not refer to any other file.

10. dup2(input_file, STDIN_FILENO) (from the project source code)\
   By default, input functions like scanf or read read data from standard input (stdin), which is usually connected to the
   keyboard. The primary purpose of dup2(input_file, STDIN_FILENO) is to redirect the standard input (stdin) of the program to read
   from input_file instead of the default.
11.  (dup2(fd[0], STDOUT_FILENO) (from the project source code)\
    The line serves the purpose of redirecting the standard output (stdout) of the current
    process to write to the pipe's read end (fd[0]) instead of the default, which is typically the terminal or console

