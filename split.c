/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/03 16:30:41 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*make_dbl_quotes(char *argv, int sngl_qt_open, int dbl_qt_open, int i)
{
	while (argv[i])
	{
		if (argv[i] == ' ' && sngl_qt_open == 0 && dbl_qt_open == 0)
			argv[i] = '"';
		else if (argv[i] == 39 && sngl_qt_open == 0 && dbl_qt_open == 0)
		{
			argv[i] = '"';
			sngl_qt_open = 1;
		}
		else if (argv[i] == 39 && sngl_qt_open == 1 && dbl_qt_open == 0)
		{
			argv[i] = '"';
			sngl_qt_open = 0;
		}
		else if (argv[i] == '"' && dbl_qt_open == 0)//
			dbl_qt_open = 1;//(indicating the start of a double-quoted string)
		else if (argv[i] == '"' && dbl_qt_open == 1)// ignore spaces within double quote
			dbl_qt_open = 0;//(indicating the end of the double-quoted string)
		else if (argv[i] == 39 && dbl_qt_open == 1)
			exit(EXIT_FAILURE);//test here coz I changed
		i++;
	}
	return (argv);
}

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
	return (i);//returns the index of the string in the envp array that starts with "PATH=". If it doesn't find such a string, it returns the index of the last element in envp.
}

char	**split_command(char *argv)
{
	char	**command_str;
	int		i;
	int		sngl_qt_open;
	int		dbl_qt_open;

	i = 0;
	sngl_qt_open = 0;
	dbl_qt_open = 0;
	argv = make_dbl_quotes(argv, sngl_qt_open, dbl_qt_open, i);
	command_str = ft_split(argv, '"');
	if (!command_str)
		return (NULL);//free here
	return (command_str);
}

char	*join_path(char *command, char **paths, int i)
{
	char	*the_path;

	if (command[0] == '/')
	{
		command = ft_strrchr(command, '/');
		if (ft_strrchr(command, '/'))
			return (0);
	}
	while (paths[i])
	{
		the_path = ft_strjoin(paths[i], "/");
		the_path = ft_strjoin(the_path, command);
		if (!the_path)
			return (free(the_path), NULL);
		if (access(the_path, F_OK) == 0)
		{
			free_str(paths);
			return (the_path);
		}
		free(the_path);
		i++;
	}
	free_str(paths);
	return (0);
}

char	*split_arg(char *argv, char **envp)
{
	char	**command;
	char	*path_to_command;
	char	**paths;
	int		i;

	i = 0;
	if (*envp == NULL)
		exit(EXIT_FAILURE);
	command = split_command(argv);
	paths = ft_split(envp[find_path(envp)] + 5, ':');//splitting the path, explanation in my git
	if (!paths)
		cmd_not_found(command);
	path_to_command = join_path(command[0], paths, 0);
	if (path_to_command != NULL && command != NULL)
		execve(path_to_command, command, envp);
	free(path_to_command);
	free_str(command);
	exit(EXIT_FAILURE);
}
