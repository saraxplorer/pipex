/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 18:16:49 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/18 17:53:52 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write2pipe_4m_input(t_pipexb pipex, int pipefd[])
{
	if (dup2(pipex.input_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
	close(pipex.input_fd);
	parse_and_execute(pipex.argv[3], pipex.envp);
}

void	write2out_4m_pipe(t_pipexb pipex, int pipefd[])
{
	if (dup2(pipex.output_fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipefd[1]);
	close(pipex.output_fd);
	parse_and_execute(pipex.argv[4], pipex.envp);
}

void	execute_pipe_std(t_pipexb pipex, int pipefd[])
{
	pid_t	child1;
	pid_t	child2;

	child1 = fork();
	if (child1 == -1)
		exit(EXIT_FAILURE);
	if (child1 == 0)
		write2pipe_4m_input(pipex, pipefd);
	child2 = fork();
	if (child2 == -1)
		exit(EXIT_FAILURE);
	if (child2 == 0)
		write2out_4m_pipe(pipex, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &pipex.status, 0);
	waitpid(child2, &pipex.status, 0);
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
}
