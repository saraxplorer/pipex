# Requirements and Edge cases 

1. **Should execute if the command is an executable like "./pipex"**

it needs to behave like bash

2. **Pipex Should Not Rely Solely on PATH for Command Search**\
  The pipex program should not search for commands only in the "PATH" because NOT all commands are located in directories listed in the PATH. While most commands are, absolute paths are outside of the PATH. Therefore, pipex cannot find commands specified with absolute paths or executables located outside the PATH if it only looks inside the PATH
So when we do unset PATH(removes the PATH environment variable from the current shell session), it should execute the part that is ouside of path.

3. **Behavior of debugging messages in pipex**\
   The debugging messages for this project will not ne shown in the stdout as soon as we dup2 it to the pipe. So before that the messages come in the stdout, then they are redirected to the output file. However, the input commands can also affect the view of them. One of the commands that allow the debugging messages in the output file is\
    ./pipex input "./pipex" "cat -e" out
# Concepts used in the project
**-Parent process:** The parent process is the original process running the main function. Here it will be ./pipex


1. fork
    ```c
   #include <unistd.h>
   pid_t fork(void);
   ```
    pid_t represents a process ID. fork creates a new process (child process) that is a duplicate of the
   calling process (parent process).\
   If fork is called once, there will be two processes (parent and child).\
   If fork is called
   **by the first child**, each process (both the parent and child from the first fork) will create a new child, resulting in a total of four
   processes.\
   If fork is called twice **by the parent** we get two children, resulting in a total of 3
   processes.\
   The fork function returns a value of 0 to the child process. It returns the child process ID (PID) to the parent
   process.

3. pid_t\
    pid_t is a data type used in C programming on Unix-like operating systems (like Linux). It stands for "process identifier type" and is used to represent process IDs (PIDs).A process ID is a unique identifier for each running process in an operating system.pid_t is defined in the header file <sys/types.h>. but it can also be used from unistd.h.The unistd.h header file includes the definition of pid_t and provides access to getpid(), which returns the process ID of the calling process.

4. access
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

5. perror
   ``` c
   #include <stdio.h>
   void perror(const char *s)
   ```
   perror is a function in C that helps to print custom error messages in standard error. It internally uses errno and strerror to
   print error messages. so it is a good practice to add their repective libraries as well but not necessary when using only perror.
   
6. open(argv[i], O_CREAT | O_WRONLY | O_TRUNC, 0644) (from the project source code)\
   this code opens a file for writing, creates it if it doesn't exist, and clears its contents if it already exists(O_TRUNC). The new
   file (if created) will have permissions that allow the owner to read and write, while others can only read.\
   6 (owner) : read(4) + write (2) = 6
   4 (group) : read (4)
   4 (others): read (4)

7. KEY-VALUE Pair
   A key-value pair is a fundamental data structure used to store data. Each key-value pair consists of two parts:\
   Key: A unique identifier for a piece of data. (NAME)\
   Value: The data associated with the key.
   Example
   in the context of environment variables:
   Key: PATH\
   Value: /usr/local/bin:/usr/bin:/bin\
   This means that the PATH environment variable has a value of /usr/local/bin:/usr/bin:/bin, which is a list of directories where
   executable programs are located.
   
8. char **envp\
   This is an array of strings (character pointers) representing the environment variables. envp stands for "environment pointer". the pointers in envp are pointing to strings that represent key-value pairs. Each string is formatted as "KEY=VALUE"\
**Understanding envp**\
What are environment variables?\
Environment variables are key-value pairs that define the environment in which a process runs. They can contain information such as paths, user preferences, or system configurations.\
Where do envp variables come from?\
When your program starts execution, the operating system initializes the execution environment, including environment variables.
envp is a pointer to an array of strings (char **), where each string represents an environment variable in the format "NAME=value".\
Accessing envp in your program:\
Even though you may not explicitly pass environment variables when running your program, envp is still provided by the operating system.
You can use envp within your program to access and manipulate environment variables if needed.

This is what it looks like:
``` c
char **envp = {
    "SHELL=/bin/bash",
    "USER=johndoe",
    "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
    "PWD=/home/johndoe",
    "HOME=/home/johndoe",
    "LOGNAME=johndoe",
    "LANG=en_US.UTF-8",
    "TERM=xterm-256color",
    "DISPLAY=:0",
    "EDITOR=vim",
    NULL
};
```
10. pipe
   ``` c
   #include <unistd.h>
   int pipe(int pipefd[2]);
   ```
   the pipe function is used to create a unidirectional communication channel. A pipe is a mechanism that allows data to flow from one process to another. pipe function takes two fd s as parameters and makes one the writing end and another the reading end\
   **Parameters**\
   **pipefd**: This is an array of two integers. After a successful call to pipe, pipefd[0] will be the file descriptor for the read end of the pipe, and pipefd[1] will be the file descriptor for the write end of the pipe.\
   To clarify, pipefd[2] does not imply three integers. Instead, it declares an array with exactly **two** integer slots. The members are pipefd[0] and pipefd[1].\
   **Return Value**\
   On success, pipe returns 0.\
   On failure, pipe returns -1 and sets errno to indicate the error.
   
11. **dup2**
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

11. **dup2(input_file, STDIN_FILENO) (an example from the src)**\
   By default, input functions like scanf or read read data from standard input (stdin), which is usually connected to the
   keyboard. The primary purpose of dup2(input_file, STDIN_FILENO) is to redirect the standard input (stdin) of the program to read
   from input_file instead of the default.
12.  **(dup2(fd[0], STDOUT_FILENO) (another example)**\
    The line serves the purpose of redirecting the standard output (stdout) of the current
    process to write to the pipe's read end (fd[0]) instead of the default, which is typically the terminal or console
13. **ft_split(envp[find_path(envp)] + 5, ':')(from the project source code)**\
    find_path returns the index of the string in the envp array that starts with "PATH=".\
    envp[find_path(envp)]: This accesses the string in the envp array that starts with "PATH=".It is something like "PATH=/usr/local/bin:/usr/bin:/bin".\
    envp[find_path(envp)] + 5: This skips the first 5 characters ("PATH=") of the string, leaving just the actual paths: "/usr/local/bin:/usr/bin:/bin".\
    ft_split("/usr/local/bin:/usr/bin:/bin", ':'): This splits the remaining string by the colon (':') character. The ft_split function is used to break the string into an array of strings, where each string is a separate path. It is split into individual directory paths because PATH contains directories separated by :

14. **Splitting the PATH Variable**\
Function: ft_split(envp[3] + 5, ':')

Input: "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
Operation: Use ft_split to split the PATH variable by ':'.
Output: array_of_paths (array of PATH directories)
``` c
array_of_paths = {
    "/usr/local/sbin",
    "/usr/local/bin",
    "/usr/sbin",
    "/usr/bin",
    "/sbin",
    "/bin",
    NULL
}
```
14. 1. **Joining Command to PATH and Finding Valid Path**\
Function: join_cmd_to_path(array_of_cmd[0], array_of_paths, 0)

Input: "ls", array_of_paths, 0
Operation:
Loop through array_of_paths and join each directory with the command.
Check if the joined path is valid (exists and executable).
Let's go through the loop:

First Iteration: i = 0

temp = ft_strjoin("/usr/local/sbin", "/") => "/usr/local/sbin/"
valid_path = ft_strjoin(temp, "ls") => "/usr/local/sbin/ls"
access("/usr/local/sbin/ls", F_OK | X_OK) => -1 (not found or not executable)
Second Iteration: i = 1

temp = ft_strjoin("/usr/local/bin", "/") => "/usr/local/bin/"
valid_path = ft_strjoin(temp, "ls") => "/usr/local/bin/ls"
access("/usr/local/bin/ls", F_OK | X_OK) => -1 (not found or not executable)
Third Iteration: i = 2

temp = ft_strjoin("/usr/sbin", "/") => "/usr/sbin/"
valid_path = ft_strjoin(temp, "ls") => "/usr/sbin/ls"
access("/usr/sbin/ls", F_OK | X_OK) => -1 (not found or not executable)
Fourth Iteration: i = 3

temp = ft_strjoin("/usr/bin", "/") => "/usr/bin/"
valid_path = ft_strjoin(temp, "ls") => "/usr/bin/ls"
access("/usr/bin/ls", F_OK | X_OK) => 0 (found and executable)
Output: "/usr/bin/ls"


15. **execve**
    ``` c
    int execve(const char *pathname, char *const argv[], char *const envp[]);
    ```
    execve() executes the program referred to by 'pathname'.  This
       causes the program that is currently being run by the calling
       process(parent) to be replaced with a new program(child).\
    Parameters\
    pathname: This is a string that specifies the path to the program you want to execute.\
    Return Value\
    If execve is successful, it does not return because the current process is replaced by the new program.\
    If there is an error, it returns -1 and sets the errno variable to indicate the error.

   **Important after using execve or if it fails**
    execve replaces the current process image with a new process image. If execve succeeds, the current process is replaced and should not return. Therefore, **any code after execve (in the same block) will ONLY execute if execve fails.**

17. **waitpid**
    ``` c
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *status, int options);
    ```
    The waitpid function allows a parent process to wait for a specific child process to change its state, which typically means the child has exited or been terminated. It ensures that the parent process doesn't exit before its child processes are done. It can also be used to handle child processes that have been stopped (but not necessarily terminated) due to receiving a signal.\
    Here’s a step-by-step of what waitpid does:\
Parent Process Calls waitpid: The parent process calls waitpid and specifies which child process it wants to wait for based on the PID.\
Waits for Child Process: The parent process is suspended (put into a waiting state) until the specified child process changes state. This change could be due to the child process terminating normally, terminating because of an unhandled signal, or being stopped.\
Retrieves Status: When waitpid returns, it stores information about the child process's state change (e.g., exit status, termination reason) in the status parameter.\
Continues Execution: After waitpid returns, the parent process can continue its execution, typically by analyzing the status to determine how the child process terminated or stopped.\
18. **WIFEXITED(status)**\
Purpose: This macro checks if the child process terminated normally (i.e., by calling exit or returning from the main function).\
Usage: It takes the status variable (which is filled by waitpid) as an argument and returns a non-zero value (true) if the child process terminated normally.\
Example: If the child process called exit(0);, then WIFEXITED(status) would be true.\
WEXITSTATUS(status)\
Purpose: This macro extracts the exit status of the child process. This is the value that the child process passed to exit or returned from main.\
Usage: It also takes the status variable as an argument and returns the exit status of the child process.\
Example: If the child process called exit(5);, then WEXITSTATUS(status) would return 5.\

**How the pipe is made?**

**Visual Summary**\
Input File -> command1 -> Pipe -> command2 -> Output File

In my source code:

**write2pipe_4m_input:**

Executes the first command with argv[2].\
Takes input from the specified input file.\
Writes the output of the first command to the write end of the pipe (pipefd[1]).

**write2out_4m_pipe:**

Executes the second command with argv[3].\
Takes input from the read end of the pipe (pipefd[0]).\
Writes the output of the second command to the specified output file.

Together, these functions set up a pipeline where the output of the first command (argv[2]) is passed through the pipe to become the input of the second command (argv[3]). This allows you to chain commands together in a manner similar to how pipes work in a shell.

**Simplified Summary**\
write2pipe_4m_input runs command1 and sends its output into a pipe.
write2out_4m_pipe runs command2 using the output from the pipe.
make_pipe sets up the pipe and ensures that these two processes work together to achieve the pipeline effect.


**PATHS**
An absolute path and a relative path are terms used to describe the location of a file or directory in a file system:

Absolute Path:

Defines the location of a file or directory starting from the root of the file system.
Always begins with the root directory marker (/ on Unix-like systems or a drive letter like C:\ on Windows).
Provides a complete path from the root to the specific file or directory.
Example (Unix-like): /home/user/documents/file.txt\
Absolute Path Example: /home/user/bin/ls


Relative Path:

Defines the location of a file or directory relative to the current working directory or another specified directory.
Does not begin with the root directory marker.
Used when referring to files or directories within the current directory or its subdirectories.
Example: documents/file.txt\
Example: ls

Key Differences:

Starting Point: Absolute paths start from the root of the file system, while relative paths start from the current working directory.
Usage: Absolute paths are useful when you need to specify an exact location in the file system, regardless of the current working directory. Relative paths are used when referring to files or directories relative to the current context.
Understanding these distinctions helps in navigating and referencing files and directories effectively within a file system.

 **We need this for parsing the envp**

This function helps locate an executable command in a list of directories, even if the command is provided as an absolute path.

### Example Scenario ### Visual Summary

**Command**: `/usr/bin/ls`  
**Array of Paths**: `["/bin", "/usr/bin", "/usr/local/bin"]`

### Step-by-Step Explanation

1. **Check if Command is an Absolute Path**:
   - The function first checks if the command starts with `/`, indicating it's an absolute path.
   - For `/usr/bin/ls`, it isolates the command name by extracting the part after the last `/`.
   - **Result**: `command` becomes `/ls`.

2. **Construct Potential Paths**:
   - The function iterates through each directory in the `array_of_paths` and constructs possible paths by combining the directory with the isolated command name.
   - Example construction:
     - For `/bin`, it creates `/bin/ls`.
     - For `/usr/bin`, it creates `/usr/bin/ls`.
     - For `/usr/local/bin`, it creates `/usr/local/bin/ls`.

3. **Check Each Path**:
   - Each constructed path is checked to see if it exists and is executable.
   - If `/usr/bin/ls` exists and is executable, this path is returned.

4. **Handle Allocation Failures**:
   - If memory allocation fails at any point, the function frees any allocated memory and returns `NULL`.





**Exit Status Codes**

*exit(EXIT_SUCCESS):*\
Indicates successful execution.\
Equivalent to exit(0).\

*exit(EXIT_FAILURE):*\
Indicates an error occurred.\
Equivalent to exit(1).

*exit(127):*\
Typically used to indicate "command not found" in shell scripts.\
In the context of C, it's usually not used directly, but might indicate a critical error or invalid command in some programs.

# Tests for pipex
from subject:  ./pipex infile "ls -l" "wc -l" outfile\
Should behave like: < infile ls -l | wc -l > outfile\
$> ./pipex infile "grep a1" "wc -w" outfile\
Should behave like: < infile grep a1 | wc -w > outfile\

More:\
Test Example 1: Counting Lines in a File\
make a file with some texts in the project folder, compile and then the following:
``` c
$ ./pipex infile "cat" "wc -l" outfile
```
Now  use another terminal for the following command in the same folder
``` c
< infile cat | wc -l > outfile
```
Explanation: cat outputs the content of infile, and wc -l counts the number of lines in that content. Both outfile content should match.\

Test Example 2: Counting Words in a File\
This 
``` c
$ ./pipex infile "cat" "wc -w" outfile
```
should behave like
``` c
< infile cat | wc -w > outfile
```
cat outputs the content of infile, and wc -w counts the number of words in that content.\

Test Example 3: Converting Text to Uppercase\
``` c
$ ./pipex infile "cat" "tr 'a-z' 'A-Z'" outfile
```
``` c
< infile cat | tr 'a-z' 'A-Z' > outfile
```
cat outputs the content of infile, and tr 'a-z' 'A-Z' converts lowercase letters to uppercase.\








