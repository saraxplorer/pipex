/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_pipe_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:08:34 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/25 18:54:44 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipe(int **pipefd, int argc)
{
	int	number_pipes;
	int	i;

	number_pipes = argc - 4;
	i = 0;
	while (i < number_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}
