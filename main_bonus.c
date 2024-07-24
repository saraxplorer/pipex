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
	array_fd = (int **)malloc((number_pipes) * sizeof(int *));
	i = 0;
	while (i < number_pipes)
	{
		array_fd[i] = (int *)malloc(2 * sizeof (int));
		if (array_fd[i] == NULL)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < number_pipes)
	{
		if (pipe(array_fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (array_fd);
}

void	free_fd(int **array_fd, int argc)
{
	int	number_pipe;
	int	i;

	number_pipe = argc - 4;
	i = 0;
	while (i < number_pipe)
	{
		free(array_fd[i]);
		i++;
	}
	free(array_fd);
}

int	execute_pipe(t_pipexb pipex)
{
	pid_t	process;
	int		command_index;
	int		pipe_index;

	command_index = 2;
	pipe_index = 0;
	while (command_index < (pipex.argc - 1))
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
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
	return (0);
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
			check_file_permission(argc, argv);
		pipex.argc = argc;
		pipex.argv = argv;
		pipex.envp = envp;
		pipex.index = 0;
		pipex.array_fd = make_pipes(argc);
		if (pipex.array_fd == NULL)
			exit(EXIT_FAILURE);
		if (execute_pipe(pipex) == 1)
			exit(EXIT_FAILURE);
	}
}
