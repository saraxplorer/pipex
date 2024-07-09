/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/08 18:46:16 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*make_dbl_quotes(char *argv, int sngl_qt_open, int dbl_qt_open, int i)
{
	while (argv[i])
	{
		//Converts spaces outside quotes into double quotes.
		if (argv[i] == ' ' && sngl_qt_open == 0 && dbl_qt_open == 0)
			argv[i] = '"';
		//Converts single quotes into double quotes 
		else if (argv[i] == 39 && sngl_qt_open == 0 && dbl_qt_open == 0)
		{
			argv[i] = '"';
			sngl_qt_open = 1;
		}
		//tracks quote states to handle nested quotes correctly. by flag sngl_quote open
		else if (argv[i] == 39 && sngl_qt_open == 1 && dbl_qt_open == 0)
		{
			argv[i] = '"';
			sngl_qt_open = 0;
		}
		else if (argv[i] == '"' && dbl_qt_open == 0)
			dbl_qt_open = 1;
		else if (argv[i] == '"' && dbl_qt_open == 1)
			dbl_qt_open = 0;
		//use dbl_quote_open to Raise an error if a single quote appears inside a double quote.
		else if (argv[i] == 39 && dbl_qt_open == 1)
			cmd_err(*ft_split(argv, '"'), 2);
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
	return (i);//Finds and returns the line number where PATH is present.
}
//Let's say envp is:
//char *envp[] = {
//     "USER=john",
//     "HOME=/home/john",
//     "PATH=/usr/bin:/bin",
//     NULL
// };On the first iteration, i is 0, and envp[0] is "USER=john" which doesn't match "PATH=", so i is incremented.
// On the second iteration, i is 1, and envp[1] is "HOME=/home/john" which doesn't match "PATH=", so i is incremented.
// On the third iteration, i is 2, and envp[2] is "PATH=/usr/bin:/bin" which matches "PATH=", so the loop breaks.
// The function then returns i, which is 2.
// So, in this example, find_path(envp) would return 2.


char	**split_command(char *argv)
{
	char	**array_of_commands;
	int		i;
	int		sngl_qt_open;
	int		dbl_qt_open;

	i = 0;
	sngl_qt_open = 0;
	dbl_qt_open = 0;
	argv = make_dbl_quotes(argv, sngl_qt_open, dbl_qt_open, i);
	//split at every single double quote resulting in separate commands, flags and a lot empty ones
	array_of_commands = ft_split(argv, '"');
	if (!array_of_commands)
		return (NULL);//free here
	return (array_of_commands);//return the commands, flags and empty double qoutes
}

char	*join_cmd_to_path(char *command, char **array_of_paths, int i)
{
	char	*valid_path;

	//if path starts from root directory
	if (command[0] == '/')
	{
		command = ft_strrchr(command, '/');//find the last /
		//ft_strrchr finds the last occurrence of '/' in the command string and sets command to point to that position. 
		//This means command now points to the last part of the path, including the '/'.
		if (ft_strrchr(command, '/') == NULL)// if / is NULL! no sense
			return (0);//stop?return to split_arg
	}
	while (array_of_paths[i])//path by path
	{
		valid_path = ft_strjoin(array_of_paths[i], "/");//join a / with path
		valid_path = ft_strjoin(valid_path, command);//join the first command after /
		if (!valid_path)
			return (free(valid_path), NULL);
		//if the joined command in the path exists
		if (access(valid_path, F_OK) == 0)
		{
			free_str(array_of_paths);
			return (valid_path);// we return valid path
		}
		free(valid_path);//free invalid path
		i++;
	}
	free_str(array_of_paths);
	return (0);//return 0 if no valid path is found
}

char	*parse_and_execute(char *argv, char **envp)
{
	char	**array_of_commands;
	char	*path_and_command;
	char	**array_of_paths;
	int		i;

	i = 0;
	if (*envp == NULL)
		exit(EXIT_FAILURE);
	array_of_commands = split_command(argv);
	array_of_paths = ft_split(envp[find_path(envp)] + 5, ':');
	if (!array_of_paths)
		cmd_not_found(array_of_commands);//not sure why command not found here?just wrong
	path_and_command = join_cmd_to_path(array_of_commands[0], array_of_paths, 0);//join path and only first command
	if (path_and_command != NULL && array_of_commands != NULL)//valid command and valid path+command
		execve(path_and_command, array_of_commands, envp);//make a new process, no need to return!
	free(path_and_command);
	free_str(array_of_commands);
	exit(EXIT_FAILURE);//exit with failure if execve fails
}
