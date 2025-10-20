/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:45:39 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/20 14:02:15 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_multiple_pipex(int argc, char **argv, char **envp)
{
	int	files[2];
	int	i;

	i = 1;
	files[0] = open_file(argv[i++], STDIN_FILENO);
	if (files[0] < 0)
		print_error("pipex", 1);
	if (dup2(files[0], STDIN_FILENO) < 0)
		print_error("pipex", 1);
	close(files[0]);
	while (i < argc - 2)
	{
		process_pipe(argv[i], envp);
		i++;
	}
	wait(NULL);
	files[1] = open_file(argv[argc - 1], STDOUT_FILENO);
	if (files[1] < 0)
		print_error("pipex", 1);
	if (dup2(files[1], STDOUT) < 0)
		print_error("pipex", 1);
	execute_cmd(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc - 1 < 5)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		printf("here_doc\n"); // Execute heredoc
	else
		init_multiple_pipex(argc, argv, envp);
	return (0);
}
