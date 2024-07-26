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

//@param fd_write Array containing file descriptors for the write end of the pipe.

void	write2pipe4minput(int fd_write[], int input_fd, t_pipexb pipex)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)// Redirect standard input to input_fd
		exit(EXIT_FAILURE);
	if (dup2(fd_write[1], STDOUT_FILENO) == -1)// Redirect standard output to the write end of the pipe
		exit(EXIT_FAILURE);
	close(fd_write[0]);// Close the unused read end of the pipe
	close(input_fd);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[2], pipex.envp);
}

//fd_read Array containing file descriptors for the read end of the pipe
void	wrt2out4mpp(int fd_read[], int out_fd, t_pipexb pipex)
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)// Redirect standard input to the read end of the pipe
		exit(EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) == -1)// Redirect standard output to out_fd
		exit(EXIT_FAILURE);
	close(fd_read[1]);// Close the unused write end of the pipe
	close(out_fd);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[pipex.argc - 2], pipex.envp);
}
/**
 * @param fd_r Array containing file descriptors for the read end of the pipe.
 * @param fd_w Array containing file descriptors for the write end of the pipe.
 * @param pipex Structure containing additional pipe-related information.
 */
void	p2p(int fd_read[], int fd_write[], t_pipexb pipex)
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_write[0]);
	close(fd_read[1]);
	close_pipe(pipex.array_fd, pipex.argc);
	parse_and_execute(pipex.argv[2 + pipex.index], pipex.envp);
}

void	set_pipe(t_pipexb pipex, int command_index, int pipe_index)
{
	// Setup for the first command: redirects input and writes to the first pipe
	if (command_index == 2 && pipe_index == 0)
		write2pipe4minput(pipex.array_fd[pipe_index], pipex.input_fd, pipex);
	// Setup for the last command: reads from the last pipe and redirects output
	else if (command_index == (pipex.argc -2))//when command index is the index of the last command
		wrt2out4mpp(pipex.array_fd[pipe_index - 1], pipex.out_fd, pipex);
	// Setup for intermediate commands: redirect input and output between pipes
	else
	{
		pipex.index++;
		p2p(pipex.array_fd[pipe_index -1], pipex.array_fd[pipe_index], pipex);
		//pipex.array_fd[pipe_index - 1]: The file descriptors for the previous pipe’s read and write ends. 
		//pipe_index - 1 is the index for the previous pipe in the sequence. 
	}
}

