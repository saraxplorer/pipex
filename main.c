/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 16:44:59 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/04 16:38:40 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	child1(int input_file, int fd[], char *argv[], char *envp[])
{
	if (dup2(input_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	close(input_file);
	split_arg(argv[2], envp);
}

void	child2(int output_file, int fd[], char *argv[], char *envp[])
{
	if (dup2(output_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	close(output_file);
	split_arg(argv[3], envp);
}

void	make_pipe(int input_file, int output_file, char *argv[], char *envp[])
{
	pid_t	process1;
	pid_t	process2;
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	//else pipe is making a unidirectional channel between fd[0] and fd[1]
	process1 = fork();
	if (process1 == -1)
		exit(EXIT_FAILURE);
	if (process1 == 0)
		child1(input_file, fd, argv, envp);//fd has both channels
	process2 = fork();
	if (process2 == -1)
		exit(EXIT_FAILURE);
	if (process2 == 0)
		child2(output_file, fd, argv, envp);//fd has both channels
	close(fd[0]);
	close(fd[1]);
	waitpid(process1, &status, 0);
	waitpid(process2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	input_file;
	int	output_file;

	if (argc != 5)
		error_exit("Error: incorrect number of arg");
	if (access(argv[1], F_OK == -1))
		error_exit("Error: input file does not exist");
	input_file = open(argv[1], O_RDONLY);
	output_file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (access(argv[1], R_OK == -1) || access(argv[argc - 1], W_OK == -1))
		error_exit("Error: permission denied");
	if (input_file < 0 || output_file < 0)
		error_exit("Error opening file");
	make_pipe(input_file, output_file, argv, envp);
	// close(input_file);
	// close(output_file);
}
