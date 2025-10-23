/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:45:39 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/23 18:39:58 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	save_output_file(char *cmd, char *envp[], int files[])
{
	if (dup2(files[WRITE], STDOUT_FILENO) < 0)
		print_error("pipex", 1);
	close(files[WRITE]);
	execute_cmd(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	files[2];
	int	i;

	if (argc - 1 < 5)
	{
		ft_putendl_fd("Not enough arguments.", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		handle_here_doc(argc, argv[2]);
		files[WRITE] = open_file(argv[argc - 1], APPEND);
	}
	else
	{
		i = 2;
		handle_multiple_pipes(argv, files);
	}
	if (files[WRITE] < 0)
		print_error("pipex", 1);
	while (i < argc - 2)
		process_pipe(argv[i++], envp);
	save_output_file(argv[argc - 2], envp, files);
	return (1);
}
