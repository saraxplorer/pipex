/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exe_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 17:54:20 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/25 18:33:09 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**split_command(char *command)
{
	char	**cmd_parts_array;

	cmd_parts_array = ft_split(command, ' ');
	if (cmd_parts_array == NULL)
		exit (EXIT_FAILURE);
	return (cmd_parts_array);
}

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

char	*is_absolute_path(char *command)
{
	if (command[0] == '/')
	{
		command = ft_strrchr(command, '/');
		return (command + 1);
	}
	return (command);
}

char	*join_cmd_to_path(char *command, char **array_of_paths, int i)
{
	char	*valid_path;
	char	*temp;

	while (array_of_paths[i])
	{
		temp = ft_strjoin(array_of_paths[i], "/");
		if (!temp)
			return (NULL);
		valid_path = ft_strjoin(temp, command);
		free (temp);
		if (valid_path == NULL)
			return (NULL);
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

char	*parse_and_execute(char *command, char **envp)
{
	char	**cmd_parts_array;
	char	*path_and_cmd;
	char	**array_of_paths;
	char	*base_command;

	cmd_parts_array = split_command(command);
	array_of_paths = ft_split(envp[find_path(envp)] + 5, ':');
	if (array_of_paths == NULL)
	{
		free_str(cmd_parts_array);
		exit (EXIT_FAILURE);
	}
	base_command = is_absolute_path(cmd_parts_array[0]);
	path_and_cmd = join_cmd_to_path(base_command, array_of_paths, 0);
	if (!path_and_cmd)
	{
		cmd_not_found(cmd_parts_array);
		free_str(array_of_paths);
	}
	if (path_and_cmd != NULL && cmd_parts_array != NULL)
		execve(path_and_cmd, cmd_parts_array, envp);
	free(path_and_cmd);
	free_str(cmd_parts_array);
	exit(EXIT_FAILURE);
}
