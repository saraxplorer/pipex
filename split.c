/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 18:58:57 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/06/25 19:22:57 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **split_command(char *argv)
{
	char	**command_str;
	int		i;
	int		quote_s;
	int		quote_d;

	i = 0;
	quote_s = 0;
	quote_d = 0;
	argv = ft_quotes(argv, quote_s, quote_d, i);
	command_str = ft_split(argv, '"');
	if (!command_str)
		return (NULL);//free here
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
}