/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 15:15:59 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/24 14:55:55 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**make_pipes(int argc)
{
	int	**array_fd;
	int	number_pipes;
	int	i;

	number_pipes = argc - 4;//remove program name, input and output files, and one arg for pipe
	//To connect n commands, you need n - 1 pipes, reduce one arg
	array_fd = (int **)malloc((number_pipes) * sizeof(int *));// Allocate memory for an array of int pointers
	if (array_fd == NULL)
		return (NULL);
	i = 0;
	while (i < number_pipes)//doing the following in a loop so making number_pipes number of twins
	{
		array_fd[i] = (int *)malloc(2 * sizeof (int));// Create a pipe and store the file descriptors in array_fd[i]
		if (array_fd[i] == NULL)
			return (NULL);
		i++;
	}
	// array_fd[i][0] is the file descriptor for the read end of the pipe
		// array_fd[i][1] is the file descriptor for the write end of the pipe
	i = 0;
	while (i < number_pipes)
	{
		if (pipe(array_fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (array_fd);
}
//The two integers in each array_fd[i] represent the file descriptors for the read and write ends of a pipe created using the pipe system call.
//pipe(array_fd[i]) creates a pipe and stores the file descriptors in the array array_fd[i].
//So, each array_fd[i] is an array of two integers: [read_fd, write_fd].

void	free_fd(int **array_fd, int argc)
{
	int	number_pipe;
	int	i;

	number_pipe = argc - 4;
	i = 0;
	while (i < number_pipe)
	{
		free(array_fd[i]);// Free each individual pipe (array of two ints)
		i++;
	}//This loop iterates through each element of array_fd (which are pointers to arrays of two integers) and frees them.
	free(array_fd);//// Free the array of pointers itself

}
//free_fd is freeing both array_fd and array_fd[i]. 

int	fork_pipe(t_pipexb pipex)
{
	pid_t	process;
	int		command_index;
	int		pipe_index;

	command_index = 2;// Start at the first command (skip program name and input file)
	pipe_index = 0;
	while (command_index < (pipex.argc - 1))// Loop through each command except the last one(output file)  beginning from argv[2](first command)
	{
		process = fork();
		if (process == -1)
			return (1);
		if (process == 0)
			set_pipe(pipex, command_index, pipe_index);
		command_index++;
		pipe_index++;
	}
	close_pipe(pipex.array_fd, pipex.argc);
	free_fd(pipex.array_fd, pipex.argc);
	close(pipex.input_fd);
	close(pipex.out_fd);
	waitpid(process, &pipex.status, 0);
	if (WIFEXITED(pipex.status)) // If the child terminated normally
		exit(WEXITSTATUS(pipex.status));// Exit with the child's exit status
	return (0);
}

void	handle_cleanup(int **array_fd, t_pipexb pipex)
{
	close(pipex.input_fd);
	close(pipex.out_fd);
	free_fd(array_fd, pipex.argc);
	error_exit("cannot make pipe/fork");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipexb	pipex;

	if (argc < 5)
		error_exit("Error: invalid number of arguments");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		heredoc(argc, argv, envp);
	else
	{
		pipex.input_fd = open(argv[1], O_RDONLY);
		pipex.out_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex.input_fd < 0 || pipex.out_fd < 0)
			diagnose_error_bonus(argc, argv);
		pipex.argc = argc;
		pipex.argv = argv;
		pipex.envp = envp;
		pipex.index = 0;
		pipex.array_fd = make_pipes(argc);
		if (pipex.array_fd == NULL)
			handle_cleanup(pipex.array_fd, pipex);
		if (fork_pipe(pipex) == 1)
			handle_cleanup(pipex.array_fd, pipex);
	}This loop iterates through each element of array_fd (which are pointers to arrays of two integers) and frees them.
}

