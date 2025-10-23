/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:49:22 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:56 by thaperei         ###   ########.fr       */
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

char	**split_literal_args(char const *str, char delimiter);
void	init_pipex(char **argv, char **envp);

// Utils functions
void	print_error(char *str, int exit_code);
void	free_arr(char **arr_str);
void	execute_command(char *full_cmd, char **envp);
#endif
