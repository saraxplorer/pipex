/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/29 18:46:44 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			return (line_num);//return the index(line_no) where path is found
		line_num++;
	}
	return (-1);//if path is not found
}

char	*join_cmd_to_path(char *command, char **array_of_paths, int i)
{
	char	*valid_path;
	char	*temp;

	puts("in join");
	while (array_of_paths[i])
	{
		temp = ft_strjoin(array_of_paths[i], "/");
		if (!temp)
			return (NULL);
		valid_path = ft_strjoin(temp, command);
		free (temp);
		if (valid_path == NULL)
			return (NULL);
		puts("after join");
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
	int		path_index;

	puts("in parse");
	cmd_parts_array = split_command(command);
	path_index = find_path(envp);
	if (path_index != -1)
		array_of_paths = ft_split(envp[path_index] + 5, ':');
	else
	{
		array_of_paths = cmd_parts_array;
	}
	if (array_of_paths == NULL)
	{
		free_str(cmd_parts_array);
		exit (EXIT_FAILURE);
	}
	if (command[0] == '/' || command[0] == '.')
	{
		puts("in if");
		path_and_cmd = ft_strdup(command);
	}
	else
	{
		path_and_cmd = join_cmd_to_path(cmd_parts_array[0], array_of_paths, 0);
		puts("after join");
	}
	if (!path_and_cmd)
	{
		cmd_not_found(cmd_parts_array);
		free_str(array_of_paths);
	}
	if (path_and_cmd != NULL && cmd_parts_array != NULL)
	{
		execve(path_and_cmd, cmd_parts_array, envp);//if execve returns, it means error
	}
	free(path_and_cmd);
	free_str(cmd_parts_array);
	exit(EXIT_FAILURE);
}
