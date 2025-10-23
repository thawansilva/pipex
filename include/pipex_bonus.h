/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:49:22 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/23 15:50:30 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
// Pipe fd's macro
# define READ 0
# define WRITE 1
# define APPEND 2

char	**split_literal_args(char const *str, char c);
// Pipex bonus
void	process_pipe(char *cmd, char *envp[]);
int		open_file(char *filename, int stream);
void	handle_multiple_pipes(char **argv, int files[2]);
void	handle_here_doc(int argc, char *limiter);

// Utils functions
void	print_error(char *str, int exit_code);
void	execute_cmd(char *full_cmd, char **envp);
#endif
