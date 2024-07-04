/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/03 14:56:43 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/03 16:46:21 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	no_perm_err(int argc, char *argv[])
{
	if (access(argv[1], F_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 29);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": permission denied\n", 21);
	}
	if (access(argv[argc - 1], W_OK | R_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[argc - 1], ft_strlen(argv[argc - 1]));
		write(2, ": permission denied\n", 21);
		exit(EXIT_FAILURE);
	}
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	cmd_not_found(char **command)
{
	write(2, "pipex: ", 7);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	free_str(command);
	exit(127);
}
