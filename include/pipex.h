/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:49:22 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/18 17:55:34 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
// Pipe fd's macro
# define READ 0
# define WRITE 1

void	pipex(char **argv, char **envp);
char	**ft_split_literal(char const *str, char c, char literal);

// Utils functions
void	error_msg(char *str, int exit_code);
void	execute_command(char *full_cmd, char **envp);
char	*get_command_path(char *full_cmd, char **envp);
void	free_arr_str(char **arr_str);
char	*get_path_env_variable(char **envp);
#endif
