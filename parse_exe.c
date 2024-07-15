/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/15 15:27:12 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	*make_dbl_quotes(char *argv, int sngl_qt_open, int dbl_qt_open, int i)
// {
// 	while (argv[i])
// 	{
// 		if (argv[i] == ' ' && sngl_qt_open == 0 && dbl_qt_open == 0)
// 			argv[i] = '"';
// 		else if (argv[i] == 39 && sngl_qt_open == 0 && dbl_qt_open == 0)
// 		{
// 			argv[i] = '"';
// 			sngl_qt_open = 1;
// 		}
// 		else if (argv[i] == 39 && sngl_qt_open == 1 && dbl_qt_open == 0)
// 		{
// 			argv[i] = '"';
// 			sngl_qt_open = 0;
// 		}
// 		else if (argv[i] == '"' && dbl_qt_open == 0)
// 			dbl_qt_open = 1;
// 		else if (argv[i] == '"' && dbl_qt_open == 1)
// 			dbl_qt_open = 0;
// 		else if (argv[i] == 39 && dbl_qt_open == 1)
// 			error_exit("ok");
// 			//cmd_err(*ft_split(argv, '"'), 2);
// 		i++;
// 	}
// 	return (argv);
// }

int	find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

char	**split_command(char *argv)
{
	char	**array_of_commands;
	int		i;
	int		sngl_qt_open;
	int		dbl_qt_open;

	(void)argv;
	i = 0;
	sngl_qt_open = 0;
	dbl_qt_open = 0;
	//argv = make_dbl_quotes(argv, sngl_qt_open, dbl_qt_open, i);
	array_of_commands = ft_split(argv, ' ');
	if (array_of_commands == NULL)
	{
		free_str(array_of_commands);
		exit (EXIT_FAILURE);
	}

	return (array_of_commands);
}

char	*join_cmd_to_path(char *command, char **array_of_paths, int i)
{
	char	*valid_path;
	char	*temp;

	if (command[0] == '/')
	{
		command = ft_strrchr(command, '/');
		if (ft_strrchr(command, '/') == NULL)
			return (0);
	}
	while (array_of_paths[i])
	{
		temp = ft_strjoin(array_of_paths[i], "/");
		valid_path = ft_strjoin(temp, command);
		free (temp);
		if (valid_path == NULL)
			exit (127);
		if (access(valid_path, F_OK | X_OK) == 0)
		{
			free_str(array_of_paths);
			return (valid_path);
		}
		free(valid_path);
		i++;
	}
	free_str(array_of_paths);
	return (0);
}

char	*parse_and_execute(char *argv, char **envp)
{
	char	**array_of_commands;
	char	*path_and_command;
	char	**array_of_paths;
	int		i;

	i = 0;
	array_of_commands = split_command(argv);
	array_of_paths = ft_split(envp[find_path(envp)] + 5, ':');
	if (array_of_paths == NULL)
		cmd_not_found(array_of_commands);
	path_and_command = join_cmd_to_path(array_of_commands[0], array_of_paths, 0);
	// if (!path_and_command)
	// 	cmd_not_found(array_of_commands);
	if (path_and_command != NULL && array_of_commands != NULL)
		execve(path_and_command, array_of_commands, envp);
	free(path_and_command);
	free_str(array_of_commands);
	exit(EXIT_FAILURE);
}
