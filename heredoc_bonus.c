/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 15:38:36 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/18 19:06:17 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*remove_newline(char *line, char *limiter)
{
	size_t	len;
	char	*substring;

	if (line == NULL)
		return (NULL);
	len = ft_strlen(line);
	// Check if there's a newline character and if limiter is not "\n"
	//test here
	if (ft_strchr(line, '\n') && limiter[0] != '\n')
		substring = ft_substr(line, 0, len - 1); // Remove the newline character
	else
		substring = ft_substr(line, 0, len);// Keep the string as is
	return (substring);
}

void	free_stdin(char *line, char *str)
{
	free(line);
	free(str);
}

void	read_stdin(t_pipexb pipex)
{
	char	*line;
	char	*limiter;
	char	*str;
	int		i;

	limiter = pipex.argv[2];
	line = get_next_line(0);
	str = remove_newline(line, limiter);
	while (line != NULL && ft_strncmp(str, limiter, ft_strlen(limiter)) != 0)
	{
		i = ft_strlen(line);
		write(pipex.input_fd, line, i);
		if (ft_strchr(line, '\n') == NULL)
			break ;
		free_stdin(line, str);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		str = remove_newline(line, limiter);
	}
	if (line != NULL && str != NULL)
		free_stdin(line, str);
}

int	heredoc(int argc, char **argv, char **envp)
{
	t_pipexb	pipex;
	int			pipefd[2];

	if (argc != 6)
		error_exit("Error: invalid number of arguments. \n");
	pipex.input_fd = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipex.output_fd = open(argv[5], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.input_fd < 0)
		perror("error: cannot open tmp_file");
	if (pipex.output_fd < 0)
		check_file_permission(argv[5]);
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	read_stdin(pipex);
	close(pipex.input_fd);
	pipex.input_fd = open("tmp_file", O_RDONLY);
	execute_pipe_std(pipex, pipefd);
	return (0);
}
