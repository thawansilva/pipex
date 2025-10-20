/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:49:22 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/19 21:15:24 by thawan           ###   ########.fr       */
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

void	init_pipex(char **argv, char **envp);
char	**ft_split_literal(char const *str, char c, char literal);
void	handle_multiple_pipes(int argc, char **argv, char **envp);

// Utils functions
void	print_error(char *str, int exit_code);
void	execute_command(char *full_cmd, char **envp);
char	*get_command_path(char *full_cmd, char **envp);
char	*get_path_env_variable(char **envp);
void	free_arr(char **arr_str);
#endif
