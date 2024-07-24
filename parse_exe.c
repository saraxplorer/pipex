/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/24 17:14:27 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path(char **envp)
{
	int	line_num;

	line_num = 0;
	while (envp[line_num])
	{
		if (ft_strncmp(envp[line_num], "PATH=", 5) == 0)
			break ;
		line_num++;
	}
	return (line_num);
}

char	**split_command(char *argv)
{
	char	**array_of_cmd;

	array_of_cmd = ft_split(argv, ' ');
	if (array_of_cmd == NULL)
	{
		free_str(array_of_cmd);
		exit (EXIT_FAILURE);
	}
	return (array_of_cmd);
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
		if (!temp)
			exit (EXIT_FAILURE);
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
	char	**array_of_cmd;
	char	*path_and_cmd;
	char	**array_of_paths;

	array_of_cmd = split_command(argv);
	array_of_paths = ft_split(envp[find_path(envp)] + 5, ':');
	if (array_of_paths == NULL)
	{
		free_str(array_of_paths);
		exit (EXIT_FAILURE);
	}
	path_and_cmd = join_cmd_to_path(array_of_cmd[0], array_of_paths, 0);
	if (!path_and_cmd)
		cmd_not_found(array_of_cmd);
	if (path_and_cmd != NULL && array_of_cmd != NULL)
		execve(path_and_cmd, array_of_cmd, envp);
	free(path_and_cmd);
	free_str(array_of_cmd);
	exit(EXIT_FAILURE);
}
