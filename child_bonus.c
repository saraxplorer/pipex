/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:34:19 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/24 14:55:55 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write2pipe4minput(int fd_w[], int input_fd, t_pipexb pipex)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_w[0]);
	close(input_fd);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[2], pipex.envp);
}

void	wrt2out4mpp(int fd_r[], int out_fd, t_pipexb pipex)
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_r[1]);
	close(out_fd);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[pipex.argc - 2], pipex.envp);
}

void	p2p(int fd_r[], int fd_w[], t_pipexb pipex)
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_w[0]);
	close(fd_r[1]);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[2 + pipex.index], pipex.envp);
}

void	set_pipe(t_pipexb pipex, int command_index, int pipe_index)
{
	if (command_index == 2 && pipe_index == 0)
		write2pipe4minput(pipex.array_fd[pipe_index], pipex.input_fd, pipex);
	else if (command_index == (pipex.argc -2))
		wrt2out4mpp(pipex.array_fd[pipe_index - 1], pipex.out_fd, pipex);
	else
	{
		pipex.index++;
		p2p(pipex.array_fd[pipe_index -1], pipex.array_fd[pipe_index], pipex);
	}
}

