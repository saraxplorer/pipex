/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 16:45:35 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/07/03 16:45:54 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"

char	*split_arg(char *argv, char **envp);

void	cmd_not_found(char **command);
void	free_str(char **str);
void	no_perm_err(int argc, char *argv[]);

#endif