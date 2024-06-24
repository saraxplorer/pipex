/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 16:44:59 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/06/24 19:56:26 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	input_file;
	int	output_file;

	if (argc != 5)
		error_exit("Error: incorrect number of arg");
	if (access(argv[1], F_OK == -1))
		error_exit("Error: input file does not exist");
	if (access(argv[1], R_OK == -1) || access(argv[argc - 1], W_OK == -1))
		error_exit("Error: permission denied");
	input_file = open(argv[1], O_RDONLY);
	output_file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (input_file < 0 || output_file < 0)
		error_exit("Error opening file");
	close(input_file);
	close(output_file);
}
