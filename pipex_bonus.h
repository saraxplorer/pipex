/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 15:16:18 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/18 18:21:51 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_pipexb
{
	int		argc;
	char	**argv;
	char	**envp;
	int		input_fd;
	int		output_fd;
	int		status;
	int		**array_of_fd;
	int		index;
}	t_pipexb;

int		main(int argc, char **argv, char **envp);

void	error_exit(char *str);
void	free_str(char **str);
void	cmd_not_found(char **command);
void	check_file_permission(char *output_file);

int		heredoc(int argc, char **argv, char **envp);
void	execute_pipe_std(t_pipexb pipex, int pipefd[]);
char	*parse_and_execute(char *argv, char **envp);


#endif