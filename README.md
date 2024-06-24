# Concepts

1. Fork: This function creates a new process (child process) that is a duplicate of the calling process (parent process). If fork is called once, there will be two processes (parent and child). If fork is called twice, each process (both the parent and child from the first fork) will create a new child, resulting in a total of four processes.The fork function returns a value of 0 to the child process. It fork function returns the child process ID (PID) to the parent process.
2. 
