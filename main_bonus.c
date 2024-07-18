/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 15:15:59 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/18 18:21:04 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	//t_pipexb	pipex;

	if (argc != 6)
		error_exit("Error: invalid number of arguments");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		heredoc(argc, argv, envp);

}
