/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 16:44:59 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/15 13:23:56 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write2pipe_4m_input(int input, int pipefd[], char *argv[], char *envp[])
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	close(input);
	parse_and_execute(argv[2], envp);
}

void	write2out_4m_pipe(int output, int pipefd[], char *argv[], char *envp[])
{
	if (dup2(output, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[1]);
	close(output);
	parse_and_execute(argv[3], envp);
}

void	make_pipe(int input_fd, int output_fd, char *argv[], char *envp[])
{
	pid_t	child1;
	pid_t	child2;
	int		status;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	child1 = fork();
	if (child1 == -1)
		exit(EXIT_FAILURE);
	if (child1 == 0)
		write2pipe_4m_input(input_fd, pipefd, argv, envp);
	child2 = fork();
	if (child2 == -1)
		exit(EXIT_FAILURE);
	if (child2 == 0)
		write2out_4m_pipe(output_fd, pipefd, argv, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	input_fd;
	int	output_fd;

	if (argc != 5)
		error_exit("Error: incorrect number of arg\n");
	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (input_fd < 0 || output_fd < 0)
		check_file_permission(argc, argv);
	make_pipe(input_fd, output_fd, argv, envp);
}
